#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
void sys_err(const char *str)
{
	perror(str);
	exit(1);
}

int main(int argc, char *argv[])
{
	int ret = mkfifo("testfifo", 0664);
	if(ret == -1)
		sys_err("mkfifo error");
	return 0;
}
