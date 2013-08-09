/*
* What is the value of the first triangle 
* number to have over five hundred divisors?
*/

var firstNumber = 0,
triangleNumbers = [],
sum = 0;

var triangle = function(){
	for(var i = 1; i < 100000; i++){
		for(var e = 1; e <= i; e++){
			sum += e;
		}
		triangleNumbers.push(sum);
		sum = 0;
		console.log(e);
	}
};

var findDivisors = function(){
	for(var i = 0; i < triangleNumbers.length; i++){
		var counter = 0;
		var e = 0;
		for(e = 0; e < triangleNumbers[e]; e++){
			if((triangleNumbers[e] % e) == 0){
				counter++;
				console.log(counter);
			}
		}
		if(counter == 500){
			firstNumber = e;
			break;
		}	
		else {
			counter = 0;
		}
	}
};

triangle();
console(triangleNumbers);
findDivisors();
console.log(firstNumber);