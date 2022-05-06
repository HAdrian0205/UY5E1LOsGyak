#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define SEMKEY 200059

int main(){

	int semid, returnV;
	union semun{
		int val;
    	struct semid_ds *buf;
		unsigned short *array;
	}arg;

	semid = semget(SEMKEY, 1, 00666 | IPC_CREAT);
	if(semid < 0){
		perror("semget hiba");
		exit(0);
	}
	returnV = semctl(semid, 0, IPC_RMID, arg);
	printf("Kill returnV: %d\n", returnV);
}
