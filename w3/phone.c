#include <stdio.h>
#include <stdlib.h>

int main(){
    int i;
    char phone_number[11];

    while(scanf("%s %d",phone_number,&i) != EOF) {
	if(i == 0){
	    printf("%s\n",phone_number);
    	}
        else{
	    printf("%c\n",phone_number[i]);
    	}
    }
    
    return 0;
}
