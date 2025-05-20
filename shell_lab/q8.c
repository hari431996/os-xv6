#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


void sigHandler(int sig){
    printf("\nI will run forever! (Use 'kill -9 %d' to terminate)\n", getpid());
}


int main(){
   
    signal(SIGINT, sigHandler);
    while(1){
            printf("c\n");
            sleep(1);

    }

    return 0;
   
}