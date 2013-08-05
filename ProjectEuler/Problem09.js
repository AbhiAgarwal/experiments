/*
* There exists exactly one Pythagorean triplet for which a + b + c = 1000.
* Find the product abc.
*/

var answer = 0,
answerF = false;

var pythagorean = function(){
	if(answerF == false){
		for(var i = 0; i < 1000; i++){
			for(var e = 0; e < 1000; e++){
				var aSquared = Math.pow(i, 2);
				var bSquared = Math.pow(e, 2);
				var cSquared = aSquared + bSquared;
				cSqrt = Math.sqrt(cSquared);

				if((i + e + cSqrt) == 1000){
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