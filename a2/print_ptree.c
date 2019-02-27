#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <ctype.h>
#include "ptree.h"


int main(int argc, char **argv) {
    // TODO: Update error checking and add support for the optional -d flag
    // printf("Usage:\n\tptree [-d N] PID\n");
    if(argc != 4 && argc != 2){
	fprintf(stderr, "Invalid Arguements\n");
	return 1;
    }

    if(argc == 4) {
    
    struct TreeNode *root = NULL;
    int c;
    char *b = NULL;
    int i;
    while((c = getopt(argc,argv,"d:")) != -1) {
	switch(c) {
	    case 'd':
		b = optarg;
		i = strtol(b,NULL,10);
		if(b == argv[2]) {
	 	    if(generate_ptree(&root,strtol(argv[3],NULL,10)) == 1) {
		        fprintf(stderr, "Failed to generate_ptree\n");
		        return 2;
		    }
		    print_ptree(root,i);
		    break;
		} else {
	 	    if(generate_ptree(&root,strtol(argv[1],NULL,10)) == 1) {
		        fprintf(stderr, "Failed to generate_ptree\n");
		        return 2;
		    }
		    print_ptree(root,i);
		}
	}
    }
    } else {

    // NOTE: This only works if no -d option is provided and does not
    // error check the provided argument or generate_ptree. Fix this!
        
    struct TreeNode *root = NULL;
    if(generate_ptree(&root, strtol(argv[1], NULL, 10)) == 1){
	fprintf(stderr, "Failed to generate_ptree\n");
	return 2;
    }
    print_ptree(root, 0);
    }

    return 0;
}

