/*
* Sum It Up
* Time Limit:3000MS
* Memory Limit:0KB
* 64bit IO Format:%lld & %llu
- Complete Search
*/
#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;
int currentNumbers[50];
map<vector<int>, bool> currentSolutions; // if a sum exists
int t, n = 0; // pre-search, t = target sum, n = number of numbers

/* Example 2 -> Algo, try similar?
    for (int mask = 1; mask < (1<<arr.length); ++mask)
    {
        ArrayList<Integer> curr = new ArrayList<Integer>();
        int sum = 0;
        for (int i = 0; i < arr.length; ++i)
        {
        int currBit = 1<<i;
        if ( (mask & currBit) != 0 )
        {
            sum += arr[i];
            curr.add(arr[i]);
        }
        }
        if (sum == 0) list.add(curr);
    }
    Collections.sort(list, new LexicoComp());
    StringBuilder sb = new StringBuilder();
    for (ArrayList<Integer> al : list)
    {
        for (int i = 0; i < al.size(); ++i)
        {
        if (i > 0) sb.append(' ');
        sb.append(al.get(i));
        }
        sb.append('\n');
    }
    System.out.print(sb);
    }
*/

// Subset sum (Example 2 -> Algo)
void search(int position, int haveWeReached, int currentSum, vector<int> d){
    int x, y = 0;
    // we found the sum, so we're going to return & print it out
    if(currentSum == t){
        if(currentSolutions[d] == true){
            return;
        } else {
            currentSolutions[d] = true;
            // Go through the numbers & print them out
            // Print all the solutions in the vector d
            for(x = 0; x < position; x++){
                // Print out as a SUM
                if(x == (position - 1)){
                    printf("%d", d[x]);
                // Print it out as a Addition Digit
                } else {
                    printf("%d+", d[x]);
                }
            }
            printf("\n");
            return;
        }
    }
    // Out of bounds -> we have gone too high, print NONE.
    if(currentSum > t || haveWeReached == n){
        return;
    }
    // Traverse the part we have left
    for(y = haveWeReached; y < n; y++){
        // Add all the combinations REALLY possible into the vector
        // d so that they can be printed out later
        d.push_back(currentNumbers[y]); // insert the number
        // increase position & haveWeReached, then add to Sum
        // Only go through each of the few iterations
        search(position + 1, y + 1, currentSum + currentNumbers[y], d);
        // Pop it out as we don't need this particular one anymore
        d.pop_back();
    }
}

int zeroSearchCase(vector<int> d){
    int i = 0;
    if(n == 1){
        printf("0\n");
    } else {
        for(i = 0; i < (n-1); i++){
            printf("0+");
        }
        printf("0\n");
    }
    d.push_back(0);
    currentSolutions[d] = true;
    return 0;
}

// Performing Complete Search
int completeSearch(){
    // Pre-search initilization
    printf("Sums of %d:\n", t);
    // Actual Search Representation
    vector<int> d;
    currentSolutions.clear();
    if(t != 0){
        search(0, 0, 0, d);
    } else {
        zeroSearchCase(d);
    }
    // If no solutions exist
    if(currentSolutions.size() == 0){
        printf("NONE\n");
    }
    return 0;
}

int main(){
    int i = 0; // loops
    while(scanf("%d %d", &t, &n) == 2){
        // Last Case
        if(t == 0 && n == 0){
            break;
        }
        // Getting all numbers
        for(i = 0; i < n; i++){
            scanf("%d", &currentNumbers[i]);
        }
        // Perform complete search
        completeSearch();
    }
    return 0;
}
