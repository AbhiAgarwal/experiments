/*
* By listing the first six prime numbers: 
* 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.
* What is the 10,001st prime number?
*/

// 10,001st prime number is going to be primeNumbers[10000];
var primeNumbers = [],
counter = 2;

var prime = function(){
	// While the length of the array isnt 10,000
	// 1000 - 1 just for the sake of clarity
	while(primeNumbers.length != (10001)){
		// Checking if the current number is True
		if(isPrime(counter) === true){
			primeNumbers.push(counter);
		}
		// Increases counter
		counter++;
	}
};

// Function to check if the number is Prime
function isPrime(n){
	// Square root of number to improve the speed
	var max = Math.sqrt(n);
    for(var i = 2; i <= max; i++ ) {
        if( n % i === 0 ){
            return false;
        }
    }
    return true;
};

// Calls prime function
prime();
// Prints the function
console.log(primeNumbers);