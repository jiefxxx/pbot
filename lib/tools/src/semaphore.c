#include <tools/semaphore.h>

int binary_semaphore_allocation (key_t key, int sem_flags){
	return semget(key,1,sem_flags);
}

int binary_semaphore_deallocate (int semid){
	return semctl (semid, 1, IPC_RMID, 0);
}
int binary_semaphore_initialize (int semid){
	return semctl(semid,0, SETALL,1);
}
int binary_semaphore_wait (int semid){
	struct sembuf operations[1];
	operations[0].sem_num = 0;
	operations[0].sem_op = -1;
	operations[0].sem_flg = SEM_UNDO;
	return semop (semid, operations, 1);
}
int binary_semaphore_post (int semid){
	struct sembuf operations[1];
	operations[0].sem_num = 0;
	operations[0].sem_op = 1;
	operations[0].sem_flg = SEM_UNDO;
 	return semop (semid, operations, 1);
}
