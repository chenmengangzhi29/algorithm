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

int send_header(struct bufferevent *bev, int no, const char *desp, const char *type, long len)
{
    char buf[256] = {0};

    spirntf(buf, "HTTP/1.1 %d %s\r\n", no, desp);
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
    chat timestr[64];
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
            
        }
    }
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
            send_error(bev);
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

const char *get_file_type(char *name)
{

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