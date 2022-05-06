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
	returnV = semctl(semid, 0, GETVAL, NULL);
	printf("Semafor value: %d\n", returnV);
}
