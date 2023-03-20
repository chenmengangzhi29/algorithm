#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

void sys_err(const char *str)
{
    perror(str);
    exit(1);
}

void sig_catch(int signo)
{
    if(signo == SIGINT){
        printf("catch you !! %d\n", signo);
        sleep(10);
    }
    else if(signo == SIGQUIT)
        printf("-------catch you !!! %d\n", signo);

    return;
}

int main(int argc, char *argv[])
{
    struct sigaction act, oldact;

    act.sa_handler = sig_catch;
    sigemptyset(&(act.sa_mask));
    act.sa_flags=0;

    int ret = sigaction(SIGINT, &act, &oldact);
    if(ret == -1)
        sys_err("sigaction error");
    ret = sigaction(SIGQUIT, &act, &oldact);

    while(1);

    return 0;
}
