#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
 #include <sys/wait.h>
 #include <stdlib.h>



int main(int argc, char *argv[])
{

   int N = 3;

   pid_t pid;
   for ( int i = 0; i < N ; i++){
      pid = fork();

      if (pid < 0)
      {
      printf("fork failed \n");
      }else if (pid == 0 ){
         printf("child - %d\n", getpid());
         exit(0); // with this only n forks are created if this is removed then 2^N -1 forks are created. 
      }
   }

   for (int i = 0; i < N; i++) {
        wait(NULL);
    }
    printf("Parent %d: All children have finished.\n", getpid());
   
   

   /*
   printf("Parent PID: %d\n", getpid());
    printf("Creating %d children...\n", N);

    pid_t pid;
    int i;
    for (i = 0; i < N; i++) {
        pid = fork();
        
        if (pid < 0) {
            // Fork failed
            perror("fork");
            return 1;
        } else if (pid == 0) {
            // Child process
            printf("Child %d PID: %d\n", i+1, getpid());
            exit(0);  // Child exits immediately
        }
        // Parent continues to the next iteration
    }

    // Parent waits for all children
    for (i = 0; i < N; i++) {
        wait(NULL);
    }

    printf("Parent %d: All children have finished.\n", getpid());
    return 0;

    */
}