#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/types.h>


// Message to print in the signal handling function. 
#define MESSAGE "%ld reads were done in %ld seconds.\n"


/* Global variables to store number of read operations and seconds elapsed.
 * These have to be global so that signal handler to be written will have
 * access.
 */
long num_reads = 0, seconds;

struct itimerval {
    struct timeval it_interval; /* next value */
    struct timeval it_value;    /* current value */
};

struct timeval {
    time_t      tv_sec;         /* seconds */
    suseconds_t tv_usec;        /* microseconds */
};

void handler(int code) {
    fprintf(stderr, "Signal %d caught\n", code);
}


int main(int argc, char ** argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: time_reads s filename\n");
        exit(1);
    }
    seconds = strtol(argv[1], NULL, 10);

    FILE *fp;
    if ((fp = fopen(argv[2], "r+")) == NULL) {    // Read+Write for later ...
      perror("fopen");
      exit(1);
    }

    struct sigaction newact;
    newact.sa_handler = handler;
    newact.sa_flags = 0;
    sigemptyset(&newact.sa_mask);
    sigaction(SIGPROF,&newact, NULL);

    sigaddset(&newact.sa_mask,SIGPROF);
    sigprocmask(SIG_BLOCK,&newact.sa_mask,NULL);

    struct itimerval val;
    val.it_interval.tv_sec = 0;
    val.it_interval.tv_usec = 0;
    val.it_value.tv_sec = seconds;
    val.it_value.tv_usec = 0;
    setitimer(ITIMER_REAL, &val,NULL);

    /* In an infinite loop, read an int from a random location in the file
     * and print it to stderr.
     */
    for (;;) {
        int randInt = rand() % 100;
        fseek(fp,sizeof(int)*randInt,SEEK_SET);
        int readint;
        fread(&readint,sizeof(int),1,fp);
        printf("%d\n",readint);
        num_reads++;
    }

    return 1;  //something is wrong if we ever get here!
}

