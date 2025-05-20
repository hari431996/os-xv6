#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
 #include <sys/wait.h>
 #include <stdlib.h>



int main(int argc, char *argv[])
{
   if (argc != 3){
      printf("Incorrect number of arguments\n");
      return 1;
   }
   int pid = fork();

   if (pid < 0)
   {
    printf("fork failed \n");
   }else if (pid == 0 ){
   
    printf("%s - %s", argv[1], argv[2]);
    int num = atoi(argv[2]);
    execlp(argv[1], argv[2], NULL);
    perror("exec");
    exit(EXIT_FAILURE);
   } else{
   //  int r = wait(NULL);
     int status;
        waitpid(pid, &status, 0); // Wait for child to finish

        if (WIFEXITED(status)) {
            printf("Command '%s %s' executed successfully.\n", argv[1], argv[2]);
        } else {
            fprintf(stderr, "Command failed to execute.\n");
            exit(EXIT_FAILURE);
        }
   }
}