#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define SEMKEY 200059

int main(){

	int semid, returnV;
	semid = semget(SEMKEY, 1, 00666 | IPC_CREAT);
	if(semid < 0){
		perror("semget hiba");
		exit(0);
	}
	returnV = semctl(semid, 0, SETVAL, 1);
	printf("set return value: %d, semval: 1\n", returnV);
}
