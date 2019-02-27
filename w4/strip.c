#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Complete this program by writing the function strip_q_marks that takes
    a single string and returns an integer.

    The function should modify the string to remove any trailing question marks
    and return the number of question marks that were removed.

    Examples
    original sentence       modified sentence       return value
    =============================================================
    "Hello? World???"       "Hello? World"          3
    "What..?"               "What.."                1
    "Apples?..?"            "Apples?.."             1
    "Coffee"                "Coffee"                0
*/

// Write the function strip_q_marks here

int strip_q_marks(char* s) {
    int len = strlen(s);
    int num_q = 0;
    int dup = 0;
    for(int i = 0; i<len;i++){
	if(s[i] == '?') {
	    num_q++;
	    dup++;
	}
    }
    if(num_q == 0){
	return num_q;
    }
    while(num_q != 1) {
	if(s[len] == '?'){
	    if(num_q == 2){
		s[len] = '\0';
	    }
	    num_q--;
	}
	len--;
    }
    int num_q_r = dup - num_q;
    return num_q_r;
}


int main(int argc, char **argv) {
    // Do not change this main function.
    if(argc != 2) {
        fprintf(stderr, "Usage: strip message\n");
        exit(1);
    }
    int result = strip_q_marks(argv[1]);
    printf("%s %d", argv[1], result);
    return 0;
}
