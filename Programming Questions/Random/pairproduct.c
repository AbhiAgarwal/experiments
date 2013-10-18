// Write to the standard output the greatest product of 2 numbers to be divisible 
// by 3 from a given array of pozitive integers.
// Example input:
// 6, 8, 8, 7, 2, 5
// Example output:
// 48

#include <stdio.h>

void max_prod(int *v, int v_length) {
    int i, x, largest, divisibleByThree, position = 0;
    for(i = 0, divisibleByThree = 0; i < v_length; i++){
    	if((v[i] % 3) == 0){       
    		if(divisibleByThree < v[i]){
        		divisibleByThree = v[i]; position = i;
    		}
    	}
    }
    for(x = 0, largest = 0; x < v_length; x++){
        if((((v[x] * divisibleByThree) % 3) == 0) && (x != position)){
            if(largest < v[x] * divisibleByThree){
                    largest = v[x] * divisibleByThree;
            }}}
    printf("%d\n", largest);
}