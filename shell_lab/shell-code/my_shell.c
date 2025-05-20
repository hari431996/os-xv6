#include  <stdio.h>
#include  <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64
#define MAX_PROCESS 64 
pid_t N_PROCESS[MAX_PROCESS];

/* Splits the string by space and returns the array of tokens
*
*/
char **tokenize(char *line)
{
  char **tokens = (char **)malloc(MAX_NUM_TOKENS * sizeof(char *));
  char *token = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));
  int i, tokenIndex = 0, tokenNo = 0;

  for(i =0; i < strlen(line); i++){

    char readChar = line[i];

    if (readChar == ' ' || readChar == '\n' || readChar == '\t'){
      token[tokenIndex] = '\0';
      if (tokenIndex != 0){
	tokens[tokenNo] = (char*)malloc(MAX_TOKEN_SIZE*sizeof(char));
	strcpy(tokens[tokenNo++], token);
	tokenIndex = 0; 
      }
    } else {
      token[tokenIndex++] = readChar;
    }
  }
 
  free(token);
  tokens[tokenNo] = NULL ;
  return tokens;
}

void execute_command(char **tokens){
		char *arg1 = tokens[0];
		int bg = 0;
		char **arg2 = tokens+1;
		int i = 0;
		while(tokens[i] != NULL){
			if (strcmp(tokens[i], "&") == 0){
				tokens[i] = NULL;
				bg = 1;
			}
			i+=1;
		}
		printf("%d\n", bg);
		if (strcmp(tokens[0], "cd") == 0){
			int error = chdir(tokens[1]);

			if (error == 0){
				printf("cd sucedded\n");
			}else{
				printf("cd failed\n");
			}

			return;
		}

		int pid = fork();
		
		if (pid < 0){
			printf("fork failed!!");
		}else if (pid == 0){
			execvp(arg1, tokens);
			perror("execution failed");
        	exit(EXIT_FAILURE);
		}else{
			
			sleep(1);
			if (bg){
				// check for process that have exited . 
				
				// store the pid in the NPROCESS Array
				for(int i = 0; i < MAX_PROCESS;i++){
					if (N_PROCESS[i] == -1){
						N_PROCESS[i] = pid;
						printf("Added to background %d\n", pid);
						break;
					}
				}
				
			} else {
				wait(NULL);
			}

			fflush(stdout);
			  fflush(stderr);
			
			
			
			// printf("parent\n");
		
		}

		return ;
}

void check_background_process(){
	for(int i = 0; i < MAX_PROCESS;i++){
		if (N_PROCESS[i] > 0){
				int status;
				pid_t waited_pid  = waitpid(N_PROCESS[i], &status, WNOHANG);

				if (waited_pid == N_PROCESS[i]){
					printf("Child %d (PID=%d) - (N_PID=%d) exited with %d\n", i+1, waited_pid,N_PROCESS[i], WEXITSTATUS(status));
						N_PROCESS[i] = -1;
				}
			}
	}
}

void cleanup(char** memory_location){
	for(int i=0;memory_location[i]!=NULL;i++){
			free(memory_location[i]);
	}
	free(memory_location);

}

void killAll(){
	printf("Entered kill\n");
	for(int i = 0; i < MAX_PROCESS; i++){
		if (N_PROCESS[i] > 0){
			printf("process pid - %d killed", N_PROCESS[i]);
			kill(N_PROCESS[i], SIGKILL);
		}
	}
}

int main(int argc, char* argv[]) {
	char  line[MAX_INPUT_SIZE];            
	char  **tokens;              
	int i;

	for(int i = 0; i < MAX_PROCESS;i++){
		N_PROCESS[i] = -1;
	}

	// check for zombie process and print if they have exited. 
	



	while(1) {			
		/* BEGIN: TAKING INPUT */

		check_background_process();
		bzero(line, sizeof(line));
		printf("$ ");
		fflush(stdout); 
		scanf("%[^\n]", line);
		getchar();

		// printf("Command entered: %s (remove this debug output later)\n", line);
		/* END: TAKING INPUT */

		if (strlen(line) == 0){
			continue;
		}

		line[strlen(line)] = '\n'; //terminate with new line

		
		tokens = tokenize(line);
   
       //do whatever you want with the commands, here we just print them
		/*
		for(i=0;tokens[i]!=NULL;i++){
			printf("found token %s (remove this debug output later)\n", tokens[i]);
		}
		*/

		if (strcmp(line, "exit\n") == 0){
			cleanup(tokens);
			// we must close all background processes .
			killAll();
			exit(0);
		}

		execute_command(tokens);
		
		
		
		// Freeing the allocated memory	
		cleanup(tokens);

	}
	return 0;
}
