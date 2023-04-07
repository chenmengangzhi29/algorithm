#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <event2/event.h>

void sys_err(const char *str)
{
    perror(str);
    exit(1);
}

int main(int argc, char *argv[])
{
    int i;

    struct event_base *base = event_base_new();

    const char **buf;

    buf = event_get_supported_methods();

    for(i = 0; i < 10; i++) {
        printf("buf[i] = %s\n", buf[i]);
    }

    return 0;
}