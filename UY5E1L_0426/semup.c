#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define SEMKEY 200059

int main(){

	int semid, returnV;
	struct sembuf sembuf, *sop;

	semid = semget(SEMKEY, 1, 00666 | IPC_CREAT);
	if(semid < 0){
		perror("semget hiba");
		exit(0);
	}
	sembuf.sem_num = 0;
	sembuf.sem_op = 1;
	sembuf.sem_flg = 0666;
	sop = &sembuf;
	returnV = semop(semid, sop, 1);
	printf("Up returnV: %d\n", returnV);
}
