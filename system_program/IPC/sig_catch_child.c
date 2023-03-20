#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
//有问题
void sys_err(const char *str)
{
    perror(str);
    exit(1);
}

void catch_child(int signo)
{
    pid_t wpid;
    int status;

    while((wpid = waitpid(-1, &status, 0)) != -1){
        if(WIFEXITED(status))
            printf("-------------catch child id %d, ret = %d\n", wpid, WEXITSTATUS(status));
    }
    return;
}

int main(int argc, char *argv[])
{
    pid_t pid;

    //阻塞
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGCHLD);

    sigprocmask(SIG_BLOCK, &set, NULL);

    int i;
    for(i = 0; i < 5; i++)
        if((pid = fork()) == 0)
            break;

    if(5 == i){
        struct sigaction act;

        act.sa_handler = catch_child;
        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;
        sigaction(SIGCHLD, &act, NULL);//注册信号捕捉函数
        //解除阻塞
        sigprocmask(SIG_UNBLOCK, &set, NULL);
        printf("I'm parent, pid = %d\n", getpid());
        while(1);
    }else {
        printf("I'm child pid = %d\n", getpid());
        return i;
    }
    return 0;
}
