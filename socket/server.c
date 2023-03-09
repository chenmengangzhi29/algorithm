#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <ctype.h>
#include <unistd.h>

#define SERV_PORT 8080

void sys_err(const char *str){
    perror(str);
    exit(1);
}

int main(){
    char buf[BUFSIZ], clie_ip[1024];

    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == lfd){
        sys_err("socket err");
    }

    struct sockaddr_in serv_addr, clie_addr;
    socklen_t clie_addr_len, clie_ip_len;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_addr.s_addr =  htonl(INADDR_ANY);

    int ret = bind(lfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if(-1 == ret){
        sys_err("bind err");
    }

    ret = listen(lfd, 128);
    if(-1 == ret){
        sys_err("listen err");
    }

    clie_addr_len = sizeof(clie_addr);
    int cfd  = accept(lfd, (struct sockaddr *)&clie_addr, &clie_addr_len);
    if(-1 == cfd){
        sys_err("accept err");
    }
    printf("cliet ip: %s, port: %d\n",
            inet_ntop(AF_INET, &clie_addr.sin_addr.s_addr, clie_ip, sizeof(clie_ip)), 
            ntohs(clie_addr.sin_port));

    while(1){
        int size = read(cfd, buf, sizeof(buf));
        if(-1 == size){
            sys_err("read err");
        }
        for(int i = 0; i < size; i++){
            buf[i] = toupper(buf[i]);
        }
        int ret = write(cfd, buf, size);
        if(-1 == ret){
            sys_err("write err");
        }
    }

    close(lfd);
    close(cfd);

    return 0;
}
