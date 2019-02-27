#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <math.h>

#include "eratosthenes.h"

int filter(int m, int readfd, int writefd) {
    int val = 0;
    while(read(readfd,&val,sizeof(int)) != 0) {
	if(val % m != 0) {
	    if(write(writefd,&val,sizeof(int)) == -1){
	  	fprintf(stderr, "writing in pipe\n");
		return 1;
	    }
	}
    }
    return 0;
}
