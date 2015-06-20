#ifndef DEF_SEMAPHORE
#define DEF_SEMAPHORE

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

int binary_semaphore_allocation (key_t key, int sem_flags);
int binary_semaphore_deallocate (int semid);
int binary_semaphore_initialize (int semid);
int binary_semaphore_wait (int semid);
int binary_semaphore_post (int semid);

#endif
