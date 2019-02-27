#include <stdio.h>
#include <stdlib.h>

int main(int argc, char**argv) {
    if(argc != 2) {
	    fprintf(stderr, "invalid\n");
    }

    FILE *fp;
    fp = fopen(argv[1], "w");
    for(int i = 0; i< 100; i++) {
	    int j = random() % 100;
	    fprintf(fp, "%d ", j);
    }
    fclose(fp);
    return 0;
}
