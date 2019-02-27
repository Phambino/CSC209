#include <stdio.h>
#include <stdlib.h>

int populate_array(int, int *);
int check_sin(int *);


int main(int argc, char **argv) {
    if(argc != 2){
	return 1;
    }

    int array[9];
    int num = strtol(argv[1], NULL, 10); 
    populate_array(num, array);
    if((check_sin(array)) == 0) {
	printf("Valid SIN\n");
    }
    else{
	printf("Invalid SIN\n");
    }  
    return 0;
}
