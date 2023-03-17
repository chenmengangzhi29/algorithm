#code repository 
## network programming
## design patterns
## system programming

###Process
```shell
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
```
### InterProcess Communication
- pipe
```shell
int pipe(int fd[2])	
```
- namedpipe
- semaphore
- messagequeue
- signal
- shared memory
- socket

### thread
```shell
pthread_t pthread_self(void)
int pthread_create(pthread_t *tid, const pthread_attr_t *attr, void*(*start_rountn)(void *), void *arg)
void pthread_exit(void *retval)
int pthread_join(pthread_t thread, void **retval)
int pthread_cancel(pthrad_t thread)
int pthtead_detach(pthread_t thread)
```
### thread synchronication
- mutex
```shell
pthread_mutex_init
pthread_mutex_destory
pthread_mutex_lock
pthread_mutex_trylock
pthread_mutex_unlock
```
- rwlock
```shell
pthread_rwlock_init
pthread_rwlock_rdlock
pthread_rwlock_wrlock
pthread_rwlock_unlock
pthread_rwlock_destroy
```
- cond
```shell
pthread_cond_init
pthread_cond_destroy
pthread_cond_wait
pthread_cond_timedwait
pthread_cond_signal
pthread_cond_broadcast
```
- semaphore
```shell
sem_init
sem_destroy
sem_wait
sem_post
```
- signal
