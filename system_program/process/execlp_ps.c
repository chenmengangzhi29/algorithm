#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
int main(){
    int fd;
    fd = open("ps.out", O_WRONLY|O_CREAT|O_TRUNC,0664);
    if(fd < 0){
        perror("open ps.out error");
        exit(1);
    }

    dup2(fd, STDOUT_FILENO);

    execlp("ps", "ps", "aux", NULL);
    close(fd);// have no need to
    return 0;
}
