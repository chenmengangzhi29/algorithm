#include <stdio.h>
#include <error.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>


void sys_err(const char* str){
	perror(str);
	exit(1);
}

void *func(void){
	pthread_exit(NULL);
	return NULL;
}

void *tfn(void *arg){
	int i = (int) arg;
	if(i == 2)
		func();
	sleep(i);
	printf("--I'm %dth thread: pid = %d, tid = %lu\n", i + 1, getpid(), pthread_self());

	return NULL;
}

int main(int argc, char *argv[]){
	int i;
	int ret;
	pthread_t tid;

	for(i = 0; i < 5; i++){
		ret = pthread_create(&tid, NULL, tfn, (void *)i);
		if(ret != 0){
			sys_err("pthread_create error");
		}
	}
	sleep(i);
	printf("I'm main, pid = %d, tid = %lu\n", getpid(), pthread_self());
	return 0;
}
