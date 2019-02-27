// TODO: Use this file for helper functions (especially those you want available
// to both executables.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>     /* inet_ntoa */
#include <netdb.h>         /* gethostname */
#include <sys/socket.h>

#include "socket.h"
#include "jobprotocol.h"

int commands_check(char job[BUFSIZE]) {
	if(strcmp(job,"jobs\n") == 0 || strcmp(job, "jobs") == 0) {
		return 0;
	} else if(strcmp(job,"kill\n") == 0 || strcmp(job, "kill") == 0) {
		return 0;
	} else if(strcmp(job,"watch\n") == 0 || strcmp(job, "watch") == 0) {
		return 0;
	} else if(strcmp(job,"run\n") == 0 || strcmp(job, "run") == 0) {
		return 0;
	} else if(strcmp(job,"exit\n") == 0 || strcmp(job, "exit") == 0) {
		return 0;
	} else {
		return 1;
	}
	return 1;
}

int getjob(int job[MAX_JOBS]){
    if(job[0] == 0) {
	printf("No currently running jobs\n");
	return 1;
    } else {
	int i = 0;
	while(job[i] != 0 && i<32) {
	    int pid = job[i];
	    printf("   %d",pid);
	    i+=1;
	}
	printf("\n");
    }
    return 0;
}
