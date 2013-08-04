/*
* A palindromic number reads the same both ways. 
* The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.
* Find the largest palindrome made from the product of two 3-digit numbers.
*/

// Palindrone Array
var palindromes = [],
palindromesLargest = 0;

var palindrome = function(){
	// Traverse through 100-999 (3 digit numbers)
	for(var i = 100; i < 1000; i++){
		// Traverse through 100-999 (3 digit numbers)
		for(var e = 100; e < 1000; e++){

			// Multiplication of the number
			var number = i * e;
			// Converts number to String
			var numberString = number.toString();
			// Finds Length as (100*100).length is 5
			var numberLength = numberString.length;
			// If the number is of length 6
			if(numberLength == 6){
				// If substring 0 == 5, 1 == 4, 2 == 3,
				if(	
					(numberString.substr(0, 1) == numberString.substr(5, 1)) &&
					(numberString.substr(1, 1) == numberString.substr(4, 1)) &&
					(numberString.substr(2, 1) == numberString.substr(3, 1))
				){
					// Push the number into the Palindrome Array
					palindromes.push(number);
				}
			}
		}
	}
};

// Call the Function
palindrome();

// Traverse through the Palindrome Array
for(var i = 0; i < palindromes.length; i++){
	if(palindromes[i] > palindromesLargest){
		palindromesLargest = palindromes[i];
	}
}
console.log(palindromesLargest);