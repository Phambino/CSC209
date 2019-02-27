#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXLINE 256
#define MAX_PASSWORD 10

#define SUCCESS "Password verified\n"
#define INVALID "Invalid password\n"
#define NO_USER "No such user\n"

int main(void) {
  char user_id[MAXLINE];
  char password[MAXLINE];
  int i, fd[2];

  if(fgets(user_id, MAXLINE, stdin) == NULL) {
      perror("fgets");
      exit(1);
  }
  if(fgets(password, MAXLINE, stdin) == NULL) {
      perror("fgets");
      exit(1);
  }

  if((pipe(fd)) == -1) {
  	perror("pipe");
	exit(1);
  }

  if((i = fork()) > 0) {
	printf("parent\n");
	if((dup2(fd[1], fileno(stdout))) == -1) {
	    perror("dup2");
	    exit(1);
	}
	
	if ((close(fd[0])) == -1) {
	    perror("close");
	}

  } else if(i == 0) {
	printf("child\n");
  } else {
      perror("fork");
      exit(1);
  }
  printf("%s", user_id);
  printf("%s", password);


  return 0;
}
