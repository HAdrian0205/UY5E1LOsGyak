#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    pid_t pid = fork();
    if(pid < 0){
        printf("Fork fail");
        exit(0);
    }else if(pid == 0){
        execl("./child", "./child", (char*)NULL);
    }
    waitpid(pid, NULL, 0);
    return 0;
}
