#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//通过execlp让子进程去执行ls命令
int main(int argc, char *argv[]){
    pid_t pid = fork();
    if(pid == -1){
        perror("fork error");
        exit(1);
    }
    else if(pid == 0){
        execlp("ls","ls", "-l", "-h", NULL);// NULL is must
        perror("exec error");
        exit(1);
    }
    else if(pid > 0){
        sleep(1);
        printf("I'm parent : %d\n", getpid());
    }
    return 0;
}
