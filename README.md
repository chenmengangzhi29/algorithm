# code repository 
## network programming
### socket
```c
htonl(local IP to network);
htons(local port to network);
ntohl(network IP to local);
ntohs(network port to local);

int inet_pton(int af, const char *src, void *dst);<local string IP to net>
const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);

int socket<int domain, int type, int protocol);
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int listen(int sockfd, int backlog);
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int setsockopt(lfd, SOL_SOKCET, SO_REUSERADDR, (void *)&opt, sizeof(opt));
int close(int fd);
int shutdown(int sockfd, int how);
```
### select
```c
int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);

void FD_CLR(int fd, fd_set *set);
int FD_ISSET(int fd, fd_set *set);
void FD_SET(int fd, fd_set *set);
void FD_ZERO(fd_set *set);
```
### poll
```c
int poll(struct pollfd *fds, nfds_t nfds, int timeout);
```
### epoll
```c
int epoll_create(int size);
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);

int flg = fcntl(cfd, F_GETFL);
flg |= o_NONBLOCK;
fcntl(cfd, F_SETFL, flg);
```


## design patterns
- singleton
## system programming

### Process
```c
pid_t fork(void)
getpid()
getppid()
int execlp(const char *file, const char *arg, ...)
int execl(const char *path, const char *arg, ...)
pid_t wait(int *status)
WIFEXITED(status) -> WEXITSTATUS(status)
WIFSIGNALED(status) -> WTERMSIG(status)
pid_t waitpid(pid_t pid, int *status, int options)
exit()
kill()

[session,daemon]
pid_t getsid(pid_t pid);
pid_t setsig(void);
```
### InterProcess Communication
- pipe
```c
int pipe(int fd[2])	
```
- namedpipe
```c
mkfifo
open(fifo,O_RDONLY)
open(fifo.O_WRONLY)
```
- mmap(shared memory)
```c
void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
int munmap(void *addr, size_t length);
ftruncate
```
- signal
```c
int kill (pid_t pid, int signum);
unsigned int alarm(unsigned int seconds);
int setitimer(int which, const struct itimerval *new_value, struct itimerval *old_value);
int raise(int sig);
void abort(void);

sigset_t set;
sigemptyset(sigset_t *set);
sigfillset(sigset_t *set);
sigaddset(sigset_t *set, int signum);
sigdelset(sigset_t *set, int signum);
sigismember(const sigset_t *set, int signum);
int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
int sigpending(sigset_t *set);

sighandler_t signal(int signum, sighandler_t handler);
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
```
- semaphore
- messagequeue
- socket

### thread
```c
pthread_t pthread_self(void)
int pthread_create(pthread_t *tid, const pthread_attr_t *attr, void*(*start_rountn)(void *), void *arg)
void pthread_exit(void *retval)
int pthread_join(pthread_t thread, void **retval)
int pthread_cancel(pthrad_t thread)
int pthtead_detach(pthread_t thread)
int pthread_kill(pthread_t thread, int sig);
```
### thread synchronication
- mutex
```c
pthread_mutex_init
pthread_mutex_destory
pthread_mutex_lock
pthread_mutex_trylock
pthread_mutex_unlock
```
- rwlock
```c
pthread_rwlock_init
pthread_rwlock_rdlock
pthread_rwlock_wrlock
pthread_rwlock_unlock
pthread_rwlock_destroy
```
- cond
```c
pthread_cond_init
pthread_cond_destroy
pthread_cond_wait
pthread_cond_timedwait
pthread_cond_signal
pthread_cond_broadcast
```
- semaphore
```c
sem_init
sem_destroy
sem_wait
sem_post
```
- signal
