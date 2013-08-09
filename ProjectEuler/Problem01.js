/*
* If we list all the natural numbers below 10 that are 
* multiples of 3 or 5, we get 3, 5, 6 and 9. 
* The sum of these multiples is 23.
* Find the sum of all the multiples of 3 or 5 below 1000.
= 233,168
*/

var sum = 0;
var Sum = function() {
	// Traverse from 1-1000 to find the sum of numbers 
	// divisible by 3 or 5.
	for(var i = 1; i < 1000; i++){
		var a = i % 5;
		var b = i % 3;
		if(a == 0 || b == 0){
			sum += i;
		}
	}
}

Sum();
console.log(sum);