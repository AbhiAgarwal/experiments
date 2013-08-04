/*
* Find the difference between the sum of the squares of the 
* first one hundred natural numbers and the square of the sum.
*/
var squaredAdd = 0,
squaredTotal = 0;

var squareFunction = function(){

	for(var i = 1; i < 101; i++){
		squaredAdd += (Math.pow(i, 2));
		squaredTotal += i;
	}

	squaredTotal = Math.pow(squaredTotal, 2);
};

squareFunction();
console.log(squaredTotal - squaredAdd);