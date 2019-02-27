// TODO: Implement populate_array
/*
 * Convert a 9 digit int to a 9 element int array.
 */
int populate_array(int sin, int *sin_array) {
    int i = 8;
    while(sin !=0){
	sin_array[i] = sin % 10;
	sin /= 10;
	i--;
    }
    return 0;
}

// TODO: Implement check_sin
/* 
 * Return 0 (true) iff the given sin_array is a valid SIN.
 */
int check_sin(int *sin_array) {
    int sum = 0;

    if(sin_array[0] == 0){
	return 1;
    }
    for(int i = 0;i<9;i++){
	if(i%2 == 0){
	    sin_array[i] = sin_array[i] * 1;
	    if(sin_array[i] > 9){
		sum = sum + (sin_array[i] - 9);
 	    } else {
		sum = sum + sin_array[i];
            } 
	} else {
	    sin_array[i] = sin_array[i] * 2;
	    if(sin_array[i] > 9){
		sum = sum + (sin_array[i] - 9);
	    } else {
		sum = sum + sin_array[i];
	    }
	}
    }

    if(sum % 10 == 0){
	return 0;
    }
    return 1;
}
