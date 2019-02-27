#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <math.h>

#include "eratosthenes.h"


int main(int argc, char *argv[]) {
    // Turning off sigpipe
    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
        perror("signal");
        exit(1);
    }

    // Your solution below ...

    if(argc != 2) {
	fprintf(stderr, "Usage:\n\tpfact n\n");
	exit(1);
    }

    int num = strtol(argv[1], NULL, 10);

    if(num < 2) {
	fprintf(stderr, "Usage:\n\tpfact n\n");
	exit(1);
    }

    int fd[2];
    if(pipe(fd) == -1) {
	perror("pipe");
	exit(1);
    }
    int val = fork();
    if (val < 0) {
	perror("fork");
	exit(1);
    }

    if (val > 0) { //parent
	int status;
	if(close(fd[0]) == -1) {
	    perror("close reading pipe");
	    exit(1);
	}
	for(int i = 2; i<=num;i++){
	    write(fd[1],&i,sizeof(int));
	}
	if(close(fd[1]) == -1){
	    perror("close writing pipe");
	    exit(1);
	}
	WIFEXITED(status);
    } else if(val == 0){ //child
	int newval;
	int count = 0;
	int factor1 = 0;
	int factor2 = 0;
	while(read(fd[0],&newval,sizeof(int)) != 0) {
	    count+=1;
	    if(newval > sqrt(num)) {
		if(factor1 == 0 && factor2 == 0) {
		    printf("%d is prime\n",num); // add number of filters
		    count = count/2-1;
		    printf("Number of filters = %d\n",count);
		    exit(0);
		} 
		else if(factor1 == 0 && factor2 > 0) {
		    printf("%d %d %d\n", num, factor2, num/factor2);
		    count = count/2;
		    printf("Number of filters = %d\n",count);
		    exit(0);
		}
		else if(factor1 > 0 && factor2 == 0) {
		    printf("%d %d %d\n", num, factor1, num/factor1);
		    count = count/2;
		    printf("Number of filters = %d\n",count);
		    exit(0);
		}
 		else {
		    printf("%d is not the product of two primes\n", num);
		    count = count/2 -1;
		    printf("Number of filters = %d\n",count);
		    exit(0);
		}
	    } else if(newval == sqrt(num)) {
		printf("%d %d %d\n", num, newval, newval);
		count = count/2;
	        printf("Number of filters = %d\n",count);
		exit(0);
	    }
	   
	    if(num % newval == 0) {
		if(factor1 == 0 && factor2 == 0) {
		    count+=2;
		    factor1 = newval;
		}
		else if(factor1 != 0 && factor2 == 0) {
		    factor2 = newval;
		}
		else {
		    printf("%d is not the product of two primes\n", num);
		    count = count/2 -2;
		    printf("Number of filters = %d\n",count);
		    exit(0);
		}
		
		if(num/newval % newval == 0) {
		    printf("%d is not the product of two primes\n", num);
		    count = count/2 -1;
		    printf("Number of filters = %d\n",count);
		    exit(0);
		}	    
	    }
	    
    	} 
	
    }
    return 0;
}
