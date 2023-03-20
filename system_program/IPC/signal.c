#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void sig_cath(int signo){
    printf("catch you!!! %d \n", signo);
    return;
}

int main(int argc, char *argv[])
{
    signal(SIGINT, sig_cath);
    while(1);
    return 0;
}
