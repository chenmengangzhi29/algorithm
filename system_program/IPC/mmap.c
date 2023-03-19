#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


void sys_err(const char* str)
{
	perror(str);
	exit(1);
}

int main(int argc, char *argv[]){
	char *p = NULL;
	int fd;

	fd = open("testmap", O_RDWR|O_CREAT|O_TRUNC, 0664);
	if(fd == -1)
		sys_err("open error");

	ftruncate(fd, 20);
	int len = lseek(fd, 0, SEEK_END);
	p = mmap(NULL, len, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if(p == MAP_FAILED)
		sys_err("mmap error");
	strcpy(p, "hello mmap");
	printf("-----%s\n", p);
	int ret = munmap(p, len);
	if(ret == -1)
		sys_err("munmap error");
	return 0;
}
