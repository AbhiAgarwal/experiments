function factorial(n){
	if(n === 0){
		return 1;
	}
	return n * factorial(n - 1);
}

// Highest Possible with this Factorial Function before "infinity"
console.log(factorial(170));