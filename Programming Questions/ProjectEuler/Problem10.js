/*
* The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
* Find the sum of all the primes below two million.
= 142,913,828,922
*/

var primeNumbers = [],
counter = 2,
sum = 0;

primeNumbers.push(2);

var prime = function(){
	// While the last element is smaller than 2,000,000
	while((primeNumbers[(primeNumbers.length - 1)]) < 2000000 ){
		// Checking if the current number is True
		if((isPrime(counter) === true)){
			primeNumbers.push(counter);
			// Adds it to the Sum
			if(counter < 2000000){
				sum += counter;
			}
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
// Prints the sum of the prime function
console.log("Sum of 2,000,000 numbers is: " + sum);