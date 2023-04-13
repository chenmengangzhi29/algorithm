#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <signal.h>
#include <ctype.h>
#include <errno.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include "libevent_http.h"

#define _HTTP_CLOSE_ "Connection: close\r\n"

int hexit(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    return 0;
}

void strencode(char* to, int tosize, const char* from)
{
    int tolen;

    for(tolen = 0; *from != '\0' && tolen + 4 < tosize; ++from) {
        if (isalnum(*from) || strchr("/_.-~", *from) != (char*)0) {
            *to = *from;
            ++to;
            ++tolen;
        } else {
            sprintf(to, "%%%02x", (int) *from & 0xff);
            to += 3;
            tolen += 3;
        }
    }
    *to = '\0';
}

void strdecode(char *to, char *from)
{
    for (; *from != '\0'; ++to, ++from){
        if (from[0] == '%' && isxdigit(from[1]) && isxdigit(from[2])) {
            *to = hexit(from[1])*16 + hexit(from[2]);
            from += 2;
        } else {
            *to = *from;
        }
    }
    *to = '\0';
}

//通过文件名获取文件的类型
char *get_file_type(const char *name)
{
    char* dot;

    //自右向左查找'.'字符，如不存在返回NULL
    dot = strrchr(name, '.');
    if (dot == NULL)
        return "text/plain; charset=utf-8";
    if (strcmp(dot, ".html") == 0 || strcmp(dot, ".htm") == 0)
        return "text/html; charset=utf-8";
    if (strcmp(dot, ".jpg") == 0 || strcmp(dot, ".jpeg") == 0)
        return "image/jpeg";
    if (strcmp(dot, ".gif") == 0)
        return "image/gif";
    if (strcmp(dot, ".png") == 0)
        return "image/png";
    if (strcmp(dot, ".css") == 0)
        return "text/css";
    if (strcmp(dot, ".au") == 0)
        return "audio/basic";
    if (strcmp(dot, ".wav") == 0)
        return "audio/wav";
    if (strcmp(dot, ".avi") == 0)
        return "video/x-msvideo";
    if (strcmp(dot, ".mov") == 0 || strcmp(dot, ".qt") == 0)
        return "video/quicktime";
    if (strcmp(dot, ".mpeg") == 0 || strcmp(dot, ".mpe") == 0)
        return "video/mpeg";
    if (strcmp(dot, ".vrml") == 0 || strcmp(dot, ".wrl") == 0)
        return "model/vrml";
    if (strcmp(dot, ".midi") == 0 || strcmp(dot, ".mid") == 0)
        return "audio/midi";
    if (strcmp(dot, ".mp3") == 0)
        return "audio/mpeg";
    if (strcmp(dot, ".mp4") == 0)
        return "video/mp4";
    if (strcmp(dot, ".ogg") == 0)
        return "application/ogg";
    if (strcmp(dot, ".pac") == 0)
        return "application/x-ns-proxy-autoconfig";

    return "text/plain; charset=utf-8";

}

void send_error(struct bufferevent* bev, int status, char *title, char *text)
{
    char buf[4096] = {0};

    sprintf(buf, "%s %d %s\r\n", "HTTP/1.1", status, title);
    sprintf(buf+strlen(buf), "Content-Type:%s\r\n", "text/html");
    sprintf(buf+strlen(buf), "Content-Length:%d\r\n", -1);
    sprintf(buf+strlen(buf), "Connection: close\r\n");
    bufferevent_write(bev, buf, strlen(buf));
    bufferevent_write(bev, "\r\n", 2);

    memset(buf, 0, sizeof(buf));

    sprintf(buf, "<html><head><title>%d %s</title></head>\n", status, title);
    sprintf(buf+strlen(buf), "<body bgcolor=\"#cc99cc\"><h4 align=\"center\">%d %s</h4>\n", status, title);
    sprintf(buf+strlen(buf), "%s\n", text);
    sprintf(buf+strlen(buf), "<hr>\n</body>\n</html>\n");
    bufferevent_write(bev, buf, strlen(buf));

    return;
}

int send_header(struct bufferevent *bev, int no, const char *desp, const char *type, long len)
{
    char buf[256] = {0};

    sprintf(buf, "HTTP/1.1 %d %s\r\n", no, desp);
    //HTTP/1.1 200 OK\r\n
    bufferevent_write(bev, buf, strlen(buf));
    //文件类型
    sprintf(buf, "Content-Type:%s\r\n", type);
    bufferevent_write(bev, buf, strlen(buf));
    //文件大小
    sprintf(buf, "Content-Length:%ld\r\n", len);
    bufferevent_write(bev, buf, strlen(buf));
    // Connecton：close
    bufferevent_write(bev, _HTTP_CLOSE_, strlen(_HTTP_CLOSE_));
    //send \r\n
    bufferevent_write(bev, "\r\n", 2);
    return 0;
}

int send_dir(struct bufferevent *bev, const char *dirname)
{
    char encoded_name[1024];
    char path[1024];
    char timestr[64];
    struct stat sb;
    struct dirent **dirinfo;
    int i;

    char buf[4096] = {0};
    sprintf(buf, "<html><head><meta charset=\"utf-8\"><title>%s</title></head>", dirname);
    sprintf(buf+strlen(buf), "<body><h1>当前目录: %s</h1><table>", dirname);
    //添加目录内容
    int num = scandir(dirname, &dirinfo, NULL, alphasort);
    for(i = 0; i < num; ++i)
    {
        //编码
        strencode(encoded_name, sizeof(encoded_name), dirinfo[i]->d_name);

        sprintf(path, "%s%s", dirname, dirinfo[i]->d_name);
        printf("########path = %s\n", path);
        if (lstat(path, &sb) < 0)
        {
            sprintf(buf+strlen(buf), 
                    "<tr><td><a href=\"%s\">%s</a></td></tr>\n",
                    encoded_name, dirinfo[i]->d_name);
        }
        else
        {
            strftime(timestr,sizeof(timestr), 
                    " %d %b   %Y %H:%M", localtime(&sb.st_mtime));
            if(S_ISDIR(sb.st_mode))
            {
                sprintf(buf+strlen(buf), 
                        "<tr><td><a href=\"%s/\">%s/</a></td><td>%s</td><td>%ld</td></tr>\n",
                        encoded_name, dirinfo[i]->d_name, timestr, sb.st_size);
            }
            else
            {
                sprintf(buf+strlen(buf),
                        "<tr><td><a href=\"%s\">%s</a></td><td>%s</td><td>%ld</td></tr>\n",
                        encoded_name, dirinfo[i]->d_name, timestr, sb.st_size);
            }
        }
        bufferevent_write(bev, buf, strlen(buf));
        memset(buf, 0, sizeof(buf));
    }
    sprintf(buf+strlen(buf), "</table></body></html>");
    bufferevent_write(bev, buf, strlen(buf));
    printf("############## Dir Read OK !!!!!!!!!!!!!\n");

    return 0;
}

// 发送服务器本地文件给 浏览器
void send_file_to_http(const char *file, struct bufferevent *bev)
{
    int n = 0, ret;
    char buf[4096] = {0};

    //打开的服务器本地文件。---- cfd能访问客户端的socket
    int fd = open(file, O_RDONLY);
    if(fd == -1) {
        // 404 错误页面
        send_error(bev, 404, "NOt Found", "No such file or direntry");
        exit(1);
    }

    while((n = read(fd, buf, sizeof(buf))) > 0) {
        ret = bufferevent_write(bev, buf, n);
        if (ret == -1) {
            printf("errno = %d\n", errno);
            if(errno == EAGAIN) {
                printf("-----------EAGAIN\n");
                continue;
            } else if (errno == EINTR) {
                printf("-----------EINTR\n");
                continue;
            } else {
                perror("send error");
                exit(1);
            }
        }
        if (ret < 4096)
            printf("-----------send ret: %d\n", ret);
    }

    close(fd);
}

int response_http(struct bufferevent *bev, const char *method, char *path)
{
    if(strcasecmp("GET", method) == 0) {
        //get method ...
        strdecode(path, path);
        char *pf = &path[1];

        if(strcmp(path, "/") == 0 || strcmp(path, "/.") == 0)
        {
            pf = "./";
        }

        printf("******http Request Resource Path = %s, pf = %s\n", path, pf);

        struct stat sb;
        if(stat(pf, &sb) < 0)
        {
            perror("open file err:");
            send_error(bev, 404, "NOt Found", "No such file or direntry");
            return -1;
        }

        if(S_ISDIR(sb.st_mode))//处理目录
        {
            //应该显示目录列表
            send_header(bev, 200, "OK", get_file_type(".html"), -1);
            send_dir(bev, pf);
        }
        else //处理文件
        {
            send_header(bev, 200, "OK", get_file_type(pf), sb.st_size);
            send_file_to_http(pf, bev);
        }
    }
    return 0;
}


void conn_readcb(struct bufferevent *bev, void *user_data)
{
    printf("************* begin call %s...........\n", __FUNCTION__);
    char buf[4096] = {0};
    char method[50], path[4096], protocol[32];
    bufferevent_read(bev, buf, sizeof(buf));
    printf("buf[%s]\n", buf);
    sscanf(buf, "%[^ ] %[^ ] %[^ \r\n]", method, path, protocol);
    printf("method[%s], path[%s], protocol[%s]\n", method, path, protocol);
    if (strcasecmp(method, "GET") == 0)
    {
        response_http(bev, method, path);
    }
    printf("******************end call %s................\n", __FUNCTION__);
}

void conn_eventcb(struct bufferevent *bev, short events, void *user_data)
{
    printf("******************* begin call %s ...........\n", __FUNCTION__);
    if (events & BEV_EVENT_EOF)
    {
        printf("Connection closed.\n");
    }
    else if (events & BEV_EVENT_ERROR)
    {
        printf("Got an error on the connection: %s\n",
                strerror(errno));
    }

    bufferevent_free(bev);
    printf("************** end call %s............\n", __FUNCTION__);
}

void signal_cb(evutil_socket_t sig, short events, void *user_data)
{
    struct event_base *base = user_data;
    struct timeval delay = {1, 0};
    printf("Caught an interrupt signal; exiting cleanly in one seconds.\n");
    event_base_loopexit(base, &delay);
}

void listener_cb(struct evconnlistener *listener,
                evutil_socket_t fd, struct sockaddr *sa, int socklen, void *user_data)
{
    printf("************begin call-------%s\n", __FUNCTION__);
    struct event_base *base = user_data;
    struct bufferevent *bev;
    printf("fd is %d\n", fd);
    bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
    if (!bev)
    {
        fprintf(stderr, "Error constructing bufferevent!");
        event_base_loopbreak(base);
        return;
    }
    bufferevent_flush(bev, EV_READ | EV_WRITE, BEV_NORMAL);
    bufferevent_setcb(bev, conn_readcb, NULL, conn_eventcb, NULL);
    bufferevent_enable(bev, EV_READ | EV_WRITE);

    printf("**************** end call ----------%s\n", __FUNCTION__);
}