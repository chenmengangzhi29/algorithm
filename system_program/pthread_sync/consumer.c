#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void sys_err(int ret, char* str){
    if(ret != 0){
        fprintf(stderr, "%s: %s\n", str, strerror(ret));
        pthread_exit(NULL);
    }
}

struct prod{
    struct prod* next;
    int val;
};

struct prod* head;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t has_product = PTHREAD_COND_INITIALIZER;

void *producer(void* arg){
    while(1){
        struct prod* product = malloc(sizeof(struct prod));
        product->val = rand() % 1000 + 1;

        printf("producer produce %d\n", product->val);
        pthread_mutex_lock(&mutex);

        product->next = head;
        head = product;

        pthread_mutex_unlock(&mutex);

        pthread_cond_signal(&has_product);
        sleep(1);
    }
    return NULL;
}

void *consumer(void* arg){
    while(1){
        int i = (int)arg;
        struct prod* eat;

        pthread_mutex_lock(&mutex);
        while(head == NULL){
            pthread_cond_wait(&has_product, &mutex);
        }
        eat = head;
        head = head->next;
        pthread_mutex_unlock(&mutex);
        printf("consumer %d comsum %d\n", i, eat->val);
        sleep(1);
    }
    return NULL;
}

int main(void){
    pthread_t p_tid;
    pthread_t c_tid[3];
    int ret;

    ret = pthread_create(&p_tid, NULL, producer, NULL);
    sys_err(ret, "pthread create fail");

    for(int i = 0; i < 3; i++){
        ret = pthread_create(&c_tid[i], NULL, consumer, (void*)i);
        sys_err(ret, "pthread create fail");
    }

    ret = pthread_join(p_tid, NULL);
    sys_err(ret,"pthread join fail"); 
    for(int i = 0; i < 3; i++){
        ret = pthread_join(c_tid[i], NULL);
        sys_err(ret, "pthread join fail");
    }
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&has_product);

    return 0;
}
