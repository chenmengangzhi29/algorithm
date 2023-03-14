#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <error.h>
#include <unistd.h>

void sys_err(const char *str)
{
    perror(str);
    exit(1);
}

void *tfn(void *arg)
{
    int i = (int)arg;
    printf("I'm the %d thread , thread id %ld\n", i,pthread_self()); 
    return (void *)i;
}

int main(int argc, char *argv[]){
    pthread_t tid[5];
    int ret;
    int retvalue;

    for(int i = 0; i < 5; i++){
        ret = pthread_create(&tid[i], NULL, tfn, (void *)i);
        if(ret != 0)
            sys_err("pthread_create error");
    }
    
    for(int i = 0; i < 5; i++){

        ret = pthread_join(tid[i], (void **)&retvalue);
        if(ret != 0)
            sys_err("pthread_join error");
        printf("child thread exit with var= %d\n", retvalue);

    }
    pthread_exit(NULL);
}

