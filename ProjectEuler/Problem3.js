/*
* The prime factors of 13195 are 5, 7, 13 and 29.
* What is the largest prime factor of the number 600851475143?
*/

// declaring primeFactors array
var primeFactors = [];

// primeFactor function
var primeFactor = function(number){
	// Traverses from 1-number to see if (number mod i == 0) 
	for(var i = 1; i < number; i ++){
		if((number % i) == 0){
			// If it does divide by zero then push it into the array
			primeFactors.push(i);
		}
	}
};

// calculate the number
primeFactor(600851475143);
// print the number
console.log(primeFactors[(primeFactors.length-1)])