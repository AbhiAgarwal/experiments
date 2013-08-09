/*
* What is the first term in the Fibonacci sequence to contain 1000 digits?
= 4,782
*/

var numbers = [],
DigitNumber = 0,
start = 0;

var fibonacci = function(numberOne, numberTwo){
	// Pushing two numbers into the array
	numbers.push(numberOne);
	start = 1;
	numbers.push(numberTwo);
	start = 2;
	// Traversal through the array to find Fibonacci sequence under 4,000,000
	// and add the sums 
	while((numbers[(numbers.length - 1)].toString()).length < 1001){
		var numberToPush = numbers[(numbers.length - 1)] + numbers[(numbers.length - 2)];
		start++;
		if((numberToPush.toString).length == 1000){
			DigitNumber = numberToPush;
			break;
		}
		numbers.push(numberToPush);
	}
};

fibonacci(1, 2);
console.log(numbers);