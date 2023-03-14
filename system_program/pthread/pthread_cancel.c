#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <error.h>
#include <unistd.h>

void sys_err(const char* str){
    perror(str);
    exit(1);
}


void *tfn(void *arg){
    while (1){
        printf("thread: pid = %d, tid = %lu\n", getpid(), pthread_self());
        sleep(1);
    }
    return NULL;
}

int main(int argc, char *argv[]){
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, tfn, NULL);
    if(ret != 0){
        sys_err("pthread_create error");
    }

    printf("main: pid = %d, tid = %lu\n", getpid(), pthread_self());
    sleep(5);

    ret = pthread_cancel(tid);
    if (ret != 0){
        sys_err("pthread cancel error");
    }

    while(1);
    pthread_exit((void *)0);
}
