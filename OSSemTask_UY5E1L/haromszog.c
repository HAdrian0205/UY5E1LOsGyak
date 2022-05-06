#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define MSGKEY 24601L

struct msgbuffer{
    long mtype;
    char mtext[50];
} sendbuffer, receivebuffer;

struct msqid_ds msgstruct;

void writeFile();
int receive();

int main()
{
    writeFile();
    int msgid;
    key_t key = MSGKEY;
    int msgflag, msgsize;

    msgflag = 00666 | IPC_CREAT;
    msgid = msgget(key, msgflag);

    sendbuffer.mtype = 1;
	
    FILE *fp;
    fp=fopen("hszogbe.txt","rt"); 
    if (!fp) {
        printf("Error: cannot open file."); 
        return -1;
    }
    
    char ch; 
    char sztr[5];
   
    int i = 0; 
    rewind(fp); 
    do {
         ch=fgetc(fp);
         sztr[i] = ch;
         i++;
    } while(ch!=EOF);
    sztr[5] = '\0';
    fclose(fp);
    
    strcpy(sendbuffer.mtext, sztr);
    msgsize = strlen(sendbuffer.mtext) + 1;
    msgsnd(msgid, (struct msgbuf *)&sendbuffer, msgsize, msgflag);
    
    receive();
    
    exit(0);
}

//Üzenet fogadás, majd fájlba kiíratás
int receive() {
    int msgid;
    key_t key = MSGKEY;
    int msgflag, msgsize, mtype;

    msgflag = 00666 | IPC_CREAT | MSG_NOERROR;

    msgid = msgget(key, msgflag);

    msgsize = 50;
    mtype = 0;

    msgctl(msgid, IPC_STAT, &msgstruct);
    
    FILE *fp;
    fp = fopen("hszogki.txt", "w");
    
    if (!fp) {
        printf("Error: cannot open file."); 
        return -1;
    }
    
    while(msgstruct.msg_qnum)
    {
        msgrcv(msgid, (struct msgbuf *)&receivebuffer, msgsize, mtype, msgflag);
        msgctl(msgid, IPC_STAT, &msgstruct);
    }
    
    int tomb[3];
    int t = 0;
    int x, y, z, q;
    for(int i = 0; i < 5; i++) {
    	if(receivebuffer.mtext[i] != ' ') {
    		tomb[t] = atoi(&receivebuffer.mtext[i]);
    		t++;
    	}
    }
    
    x=tomb[0];
    y=tomb[1];
    z=tomb[2];
    
    if((x+y > z) && (x+z > y) && (y+z > x)) {
    	q = 1;
    	fprintf(fp, "%d %d %d %d", x, y, z, q);
    	fclose(fp);
    	msgctl(msgid, IPC_RMID, NULL);
	for(int k = 0; k < 3; k++) {
    		printf(".\n");
    	}
    	printf("A program sikeresen lefutott!\n\n");
    	printf("A haromszog: megszerkesztheto!\n");
    	return 1;
    } else {
    	q = 0;
    	fprintf(fp, "%d %d %d %d", x, y, z, q);
    	fclose(fp);
    	for(int k = 0; k < 3; k++) {
    		printf(".\n");
    	}
    	printf("A program sikeresen lefutott!\n\n");
    	msgctl(msgid, IPC_RMID, NULL);
    	printf("A haromszog: nem megszerkesztheto!\n");
    	return 0;
    }
    
    exit(0);
}

//A fájl feltöltéséhez
void writeFile() {
    int x, y, z;
    printf("Adja meg a haromszog 3 oldalat (pl. 3 5 7)\n");
    fscanf(stdin,"%d %d %d", &x,&y,&z);
    FILE *fp;
    fp = fopen("hszogbe.txt", "w");
    if (!fp) {
        printf("Error: cannot open file."); 
        exit(0);
    }
    fprintf(fp, "%d %d %d", x, y, z);
    fclose(fp);   
}
