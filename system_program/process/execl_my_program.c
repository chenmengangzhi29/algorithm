#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    pid_t pid = fork();
    if(pid == -1){
        perror("fork error");
        exit(1);
    }
    else if(pid == 0){
        execl("./my_program", "./my_program", NULL);//NULL is must
        perror("exec error");
        exit(1);
    }
    else if(pid > 0){
        sleep(1);
        printf("I'm parent : %d\n", getpid());
    }
    return 0;
}
