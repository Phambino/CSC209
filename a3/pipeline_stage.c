#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <math.h>

#include "eratosthenes.h"

pid_t make_stage(int m, int read_fd, int **fds) { 
    int pval = pipe(*fds);
    if(pval == -1) {
	perror("pipe");
	exit(1);
    }
    int retval = fork();
    if(retval<0) {
	perror("fork");
	exit(2);
    } else if (retval > 0) {
	if((close((*fds)[0])) == -1){
	    perror("close");
	    exit(1);
	}
	if(filter(m,read_fd,(*fds)[1]) == -1){
	    perror("filter");
	    exit(1);
	}
	if(close(read_fd) == 1) {
	    perror("close");
	    exit(1);
	}
	if((close((*fds)[1])) == -1){
	    perror("close");
	    exit(1);
	}
	return retval;
    } else {
	if (close((*fds)[1]) == -1) {
	    perror("close");
	    exit(1);
	}
	if(close(read_fd) == -1) {
	    perror("close");
	    exit(1);
	}
	return 0;
    }
    return 0;
}
