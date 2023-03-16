#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	int i;
	for(i = 0; i < 5; i++){
		if(fork()==0){
			break;
		}
	}
	if(i == 5){
		sleep(i);

		printf("I'm parent \n");
	}else{
		sleep(i);
		printf("I'm %dth child\n", i + 1);
	}
	return 0;
}
