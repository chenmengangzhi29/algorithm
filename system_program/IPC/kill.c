#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
void sys_err(const char* str){
    perror(str);
    exit(1);
}

int main(int argc, char *argv[]){
    pid_t pid = fork();

    if(pid > 0){
        printf("parent, pid = %d\n", getpid());
        while(1);
    }
    else if(pid == 0){
        printf("child pid = %d, ppid = %d\n", getpid(), getppid());
        sleep(2);
        kill(getppid(), SIGKILL);
    }

    return 0;
}

