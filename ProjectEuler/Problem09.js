/*
* There exists exactly one Pythagorean triplet for which a + b + c = 1000.
* Find the product abc.
*/

var answer = 0,
answerF = false;

var pythagorean = function(){
	// if answer hasn't been set before
	// first loop
	for(var i = 0; i < 1000; i++){
		if(answerF == false){
			// second loop
			for(var e = 0; e < 1000; e++){
				// Finding a^2
				var aSquared = Math.pow(i, 2);
				// Finding b^2
				var bSquared = Math.pow(e, 2);
				// c^2 = a^2 + b^2
				var cSquared = aSquared + bSquared;
				// SquareRoot(c^2)
				cSqrt = Math.sqrt(cSquared);
				// If a + b + c = 1000
				if((i + e + cSqrt) == 1000){
					// Returns a * b * c
					answer = (i * e * cSqrt);
					answerF = true;
					console.log(answer);
					break;
				}
			}
		}
	}
};

pythagorean();