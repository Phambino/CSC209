#include <stdio.h>
#include <stdlib.h>


// TODO: Implement a helper named check_permissions that matches the prototype below.
int check_permissions(char * perm1, char * perm2){
    for(int i = 0;i<9; i++){
	if(perm1[i+1] != perm2[i]){
	    if(perm1[i+1] == '-') {
		continue;
	    }
	} else if(perm1[i+1] != perm2[i]){
	    if(perm1[i+1] != '-') {
	 	return 1;
	    }
	}
    }
    return 0;
}


int main(int argc, char** argv) {
    if (!(argc == 2 || argc == 3)) {
        fprintf(stderr, "USAGE:\n\tcount_large size [permissions]\n");
        return 1;
    }
    int count = 0;
    int csize = strtol(argv[1], NULL, 10);
    char perm[10];
    int size;

    scanf("%*s %*s");
    
    while(scanf("%s %*s %*s %*s %d %*s %*s %*s %*s", perm, &size) != EOF) {
	if(argc == 2) {
	    if(size > csize){
		count++;
	    }
	} else if (argc == 3) {
	    if(size > csize && (check_permissions(argv[2], perm)) == 0){
		count++;
	    }
	}
    }
    printf("%d\n",count);

    return 0;
}
