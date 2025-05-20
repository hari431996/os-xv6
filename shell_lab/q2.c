#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
 #include <sys/wait.h>



int main(int argc, char *argv[])
{
   int pid = fork();

   if (pid < 0)
   {
    printf("fork failed \n");
   }else if (pid == 0 ){
    printf("I am child  -- %d\n", getpid());
   } else{
   //  int r = wait(NULL);
   int *cstat;
   int r = waitpid(pid,cstat , 0);
   printf("I am parent - child pid %d  - %d\n", r, cstat);
   }
}