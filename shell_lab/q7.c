#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void signalHandler(int sig){
    printf(" exiting the child");
    exit(0);
}


int main(){
    int pid = fork();


    if (pid < 0){
        printf("Fork failed");
    }else if (pid == 0){
        signal(SIGINT, signalHandler); // once kill is called with sigkill the child process is killed immediately without any all to signalHandler. 
        printf("child\n");
        sleep(300);
    }else{
       
         sleep(10);
         kill(pid, SIGKILL);
         wait(NULL);
        printf("I am parent\n");
    }
}