#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "socket.h"
#include "jobprotocol.h"


int main(int argc, char **argv) {
    // This line causes stdout and stderr not to be buffered.
    // Don't change this! Necessary for autotesting.
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    if (argc != 2) {
        fprintf(stderr, "Usage: jobclient hostname\n");
        exit(1);
    }

    int soc = connect_to_server(PORT, argv[1]);
    char buf[BUFSIZE + 1];


    while (1) {
	    int num_read = read(STDIN_FILENO, buf, BUFSIZE);
	    if(num_read == 0) {
	        break;
	    }
	    buf[num_read] = '\0';
        char *mess = strtok(buf," ");
        if(commands_check(mess) == 0) {
	        int num_written = write(soc, buf, num_read);
	        if(num_written != num_read) {
	            perror("client: write");
	            close(soc);
	            exit(1);
	        }
        } else {
            printf("Invalid Command\n");
        }

    }

    /* TODO: Accept commands from the user, verify correctness 
     * of commands, send to server. Monitor for input from the 
     * server and echo to STDOUT.
     */


    close(soc);
    return 0;
}
