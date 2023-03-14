#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void *tfn(void *arg)
{
    printf("thread: pid = %d, tid = %lu\n", getpid(), pthread_self());
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t tid;
    pthread_attr_t attr;
    int ret = pthread_attr_init(&attr);
    if(ret != 0){
        fprintf(stderr, "attr_init error:%s\n", strerror(ret));
        exit(1);
    }
    ret = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if(ret != 0){
        fprintf(stderr, "attr_setdetachstate error:%s\n", strerror(ret));
        exit(1);
    }

    ret = pthread_create(&tid, &attr, tfn, NULL);
    if(ret != 0){
        fprintf(stderr, "pthread_create error:%s\n", strerror(ret));
        exit(1);
    }

    ret = pthread_attr_destroy(&attr);
    if(ret != 0){
        fprintf(stderr, "pthread_attr_destroy error:%s\n", strerror(ret));
        exit(1);
    }
    ret = pthread_join(tid, NULL);
    if(ret != 0){
        fprintf(stderr, "pthread_join error:%s\n", strerror(ret));
        exit(1);
    }

    printf("main: pid = %d, tid = %lu\n", getpid(), pthread_self());
    pthread_exit((void*)0);
}
