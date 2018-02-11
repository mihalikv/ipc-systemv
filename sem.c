#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define SLEEP 0.5

union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
	struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                           (Linux-specific) */
};

int sem_get_test(key_t keyval, int numsems) {
    int sid;
        
    if((sid = semget(keyval, numsems, IPC_CREAT | 0666)) == -1) {
        printf("SEMGET: Something goes wrong\n");   
		return -1;
    }
    printf("SEMGET: Success\n");   
    return sid;
}

int sem_ctl_test(int semid, int numsems, int flag) {
	union semun arg;

    if(semctl(semid, numsems, flag, arg) == -1)
    {
        printf("SEMCTL: Something goes wrong| CMD: %d | ERR: %d\n", flag, errno);   
		return -1;
    }
    printf("SEMCTL: Success| CMD: %d\n", flag);   
    return 0;
}
int main(void) {
	int sid;
	int i;
	int operations[12] = {IPC_STAT, IPC_SET, IPC_RMID, SEM_INFO, SEM_STAT, GETALL, GETNCNT, GETPID, GETVAL, GETZCNT, SETALL, SETVAL};
    
	sid = sem_get_test(5, 1);
    sleep(SLEEP);
 
	for(i=0; i < (sizeof(operations)/sizeof(int)); i++){
		sem_ctl_test(5, 1, operations[i]);
    	sleep(SLEEP); 
	}
    return 0;
}
