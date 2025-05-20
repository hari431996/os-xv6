#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
 #include <sys/wait.h>
 #include <stdlib.h>



int main(int argc, char *argv[])
{
   int pid = fork();

   if (pid < 0)
   {
    printf("fork failed \n");
   }else if (pid == 0 ){
    printf("I am child  -- %d\n", getpid());
    char *arge[] = {"-l", NULL};
    int r = execlp("sleep", "sleep", "10", NULL);
   } else{
   //  int r = wait(NULL);
   wait(NULL);
   printf("I am parent - \n");
   }
}