#include <stdio.h>

// Given an array containing all numbers from 1 to N with the 
// exception of one print the missing number to the standard output.
// Example input:
// array: 5 4 1 2
// Example output:
// 3

void find_missing_number(int *v, int v_length) {
    int i, totalReal, x, totalExpected;
    for(x = 1, totalExpected = 0; x <= (v_length); x++){totalExpected += (x);}
    for(i = 0, totalReal = 0; (i < v_length - 1); i++){totalReal += v[i];}
    printf("%d\n", (totalExpected - totalReal));
}

int main(){
	int array[4] = {2, 3, 4, 5};
	find_missing_number(array, 5);
	return 1;
}