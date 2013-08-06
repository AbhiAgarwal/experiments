/*
* What is the value of the first triangle 
* number to have over five hundred divisors?
*/

var firstNumber = 0,
triangleNumbers = [],
sum = 0;

var triangle = function(){

	for(var i = 1; i < 10000; i++){
		for(var e = 1; e <= i; e++){
			sum += e;
		}
		triangleNumbers.push(sum);
		sum = 0;
	}
};

triangle();
console.log(triangleNumbers[2]);