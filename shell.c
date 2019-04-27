#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_LEN 255

int main(void) {
  char *args[MAX_LEN / 2 + 1]; 
  int running = 1;          
  int background = 0;

  char *input;
  int status;

  while (running) {
    printf(">>> ");
    fflush(stdout);

    input = (char*)malloc(MAX_LEN*sizeof(char));
    fgets(input,MAX_LEN,stdin);
    
    char *p = strtok(input, " \n");

    int i = 0;
    args[i] = p;
    while (p != NULL) {
      i++;
      p = strtok(NULL, " \n");
      args[i] = p;
    }

    if (args[0] == NULL)
      goto no_input;

    if (strcmp(args[0], "exit") == 0) {
      break;
    }

    if (strcmp(args[i-1], "&") == 0) {
      args[i - 1] = NULL;
      background = 1;
    } else {
	    background = 0;
    }

    pid_t pid = fork();
    if (pid < 0) {
      perror("Fork error");
      exit(0);
    }

    if (pid == 0) {
		execvp(args[0], args);
    }

    if (pid > 0) {
      if (!background) {
		int status;
		waitpid(pid,&status,0);

      } 

    }
no_input:;
  }

  return 0;
}
