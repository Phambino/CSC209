#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "socket.h"
#include "jobprotocol.h"


#define QUEUE_LENGTH 5

#ifndef JOBS_DIR
    #define JOBS_DIR "jobs/"
#endif

struct job {
    pid_t pid;
    struct job *next_job;
};

struct sockname {
    int sock_fd;
    char *username;
};

int setup_new_client(int fd, struct sockname *usernames) {
    int user_index = 0;
    while (user_index < QUEUE_LENGTH && usernames[user_index].sock_fd != -1) {
        user_index++;
    }

    int client_fd = accept_connection(fd);
    if (client_fd < 0) {
        return -1;
    }

    if (user_index >= QUEUE_LENGTH) {
	fprintf(stderr, "server: max concurrent connections\n");
	close(client_fd);
	return -1;
    }

    usernames[user_index].sock_fd = client_fd;
    usernames[user_index].username = NULL;
    return client_fd;
}

int read_from(int client_index, struct sockname *usernames) {
    int fd = usernames[client_index].sock_fd;
    char buf[BUFSIZE + 1];

    int num_read = read(fd, &buf, BUFSIZE);
    buf[num_read] = '\0';
    
    if(usernames[client_index].username == NULL) {
	usernames[client_index].username = malloc(sizeof(char) * BUFSIZE);
    }

    strncpy(usernames[client_index].username, buf,BUFSIZE);

    if (num_read == 0 || write(fd, buf, strlen(buf)) != strlen(buf)) {
	    usernames[client_index].sock_fd = -1;
   	    return fd;
    }
    return 0;
}


int main(void) {
    // This line causes stdout and stderr not to be buffered.
    // Don't change this! Necessary for autotesting.
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    struct sockaddr_in *self = init_server_addr(PORT);
    int listenfd = setup_server_socket(self, QUEUE_LENGTH);
    struct sockname usernames[QUEUE_LENGTH];
    for(int index = 0; index < QUEUE_LENGTH; index++) {
	usernames[index].sock_fd = -1;
	usernames[index].username = NULL;
    }
    //int jobs_list[MAX_JOBS];


    /* TODO: Initialize job and client tracking structures, start accepting
     * connections. Listen for messages from both clients and jobs. Execute
     * client commands if properly formatted. Forward messages from jobs
     * to appropriate clients. Tear down cleanly.
     */
    int max_fd = listenfd;
    fd_set all_fds, listen_fds;
    FD_ZERO(&all_fds);
    FD_SET(listenfd, &all_fds);

    while (1) {
	listen_fds = all_fds;
	int nready = select(max_fd + 1, &listen_fds, NULL,NULL,NULL);
	if (nready == -1) {
	    perror("server: select");
	    exit(1);
 	}
	
	if(FD_ISSET(listenfd, &listen_fds)) {
	    int client_fd = setup_new_client(listenfd, usernames);
	    if(client_fd < 0) {
		continue;
	    }
	    if(client_fd > max_fd) {
		max_fd = client_fd;
	    }
	    FD_SET(client_fd, &all_fds);
	    printf("Accepted connection\n");
	}

        for (int index = 0; index < QUEUE_LENGTH; index++) {
            if (usernames[index].sock_fd > -1 && FD_ISSET(usernames[index].sock_fd, &listen_fds)) {
                // Note: never reduces max_fd
                int client_closed = read_from(index, usernames);
                if (client_closed > 0) {
                    FD_CLR(client_closed, &all_fds);
                    close(client_closed);
                    printf("Client %d disconnected\n", client_closed);
                } else {
                    printf("Echo message from connection: %d\n", usernames[index].sock_fd);
                    if(commands_check(usernames[index].username) != 0) {
                        printf("Invalid Command");
                    } else {
                        if(strcmp(strtok(usernames[index].username," "), "run\n") == 0) {
                            printf("Missing file and arguements\n");
                        }
                        if(strcmp(strtok(usernames[index].username," "), "run") == 0) {
                            printf("good\n");
                        }
                    }
                }
            }
        }
    }

    /* Here is a snippet of code to create the name of an executable to execute:
     * char exe_file[BUFSIZE];
     * sprintf(exe_file, "%s/%s", JOBS_DIR, <job_name>);
     */


    free(self);
    close(listenfd);
    return 0;
}

