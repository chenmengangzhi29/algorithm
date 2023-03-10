#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define SERV_IP "127.0.0.1"
#define SERV_PORT 8080

void sys_err(const char* msg){
    perror(msg);
    exit(1);
}

int main(){
    int cfd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == cfd){
        sys_err("socket err");
    }
    
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    int ret = inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr.s_addr);
    if(1 != ret){
        sys_err("inet_pton err");
    }

    ret = connect(cfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if(-1 == ret){
        sys_err("connect err");
        exit(1);
    }
    char* buf[BUFSIZ];
    int count = 10;
    while(count --){
        ret = write(cfd, "hello\n", 6);
        if(-1 == ret){
            sys_err("write err");
        }
        ret = read(cfd, buf, sizeof(buf));
        if(-1 == ret){
            sys_err("read err");
        }
        write(STDOUT_FILENO, buf, ret);
        sleep(1);
    }
    close(cfd);
    return 0;
}