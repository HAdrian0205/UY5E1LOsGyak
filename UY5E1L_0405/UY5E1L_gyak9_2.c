#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sigterm(int sigCode)
{
    printf("\n%d\n", sigCode);
}

int main()
{
    if(signal(SIGTERM, sigterm) == SIG_ERR)
    {
        printf("Hiba!");
        exit(1);
    }
    while(1)
    {
        sleep(3);
    }
    return 0;

}
