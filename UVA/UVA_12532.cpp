/*
- Interval Product
*/

// How can one forget stdio.h for any reason..
#include <iostream>
#include <cstring>
#include <stdio.h>
using namespace std;

class Fenwick{
public:
    static const int MAX_SIZE = 1<<18;
    int fen[MAX_SIZE];
    void adjust(int i, int adj){
        while (i < MAX_SIZE){
            fen[i] += adj;
            i += (i & (-i));
        }
    }
    int sumQuery(int k){
        int ret = 0;
        while(k > 0){
            ret += fen[k];
            k &= k-1;
        }
        return ret;
    }
    int sumQueryRange(int a, int b){return sumQuery(b) - sumQuery(a - 1);}
    // changing this from MAX_SIZE to sizeof(fen) made the
    // whole difference
    void clear(){memset(fen, 0, sizeof(fen));}
    int getValue(int i){return sumQueryRange(i, i);}
    // No need of implementing findFirst so left it out
}A, B;

void changeInformation(int a, int b, int c){
    if(b < 0){
        A.adjust(a, c);
    }
    if(b == 0){
        B.adjust(a, c);
    }
}

int main(){
    int traversalArray[1<<18];
    int a, b, c, d; // information storage
    int i, j; // for loop
    // First 2 positions _,_ to give size
    while(scanf("%d %d", &a, &b) == 2){
        // Resetting the used variables
        A.clear();
        B.clear();
        i = j = 0;
        // this actually helps print the right answer?
        char CorP[2]; // to get the C/P
        // Getting Initial Sequence
        // Start with the 1th INDEX NOT ZEROTH!!!!!!!!
        for(i = 1; i <= a; i++){
            scanf("%d", traversalArray + i); // Read into Array
            changeInformation(i, traversalArray[i], 1);
        }
        // Getting main P/C chain
        for(j = 0; j < b; j++){
            // One value in P/C
            scanf("%s %d %d", CorP, &c, &d);
            // Simplfy the program a little, & product section
            if(*CorP == 'P'){
                if(B.sumQueryRange(c, d)){putchar('0');}
                else {
                    if(A.sumQueryRange(c, d) % 2){putchar('-');}
                    else {putchar('+');}
                }
            } else { // Change Value == 'C'
                // We want to change values not product them
                changeInformation(c, traversalArray[c], -1);
                // assign/change value & restructure
                traversalArray[c] = d; // set value
                changeInformation(c, traversalArray[c], 1);
            }
        }
        puts("");
    }
}
