/*
* What is the smallest positive number that is 
* evenly divisible by all of the numbers from 1 to 20?
* */

/*
The concept of this answer is the fact that it won't set it to true again,
and if it is set to false once then it breaks out of the loop.
*/

var smallest = function(){
	// Goes through numbers from 1 - 10000000000
	for(var i = 0; i < 10000000000; i++){
		// Variable to check if it has been found
		var found = true;
		// Goes through numbers from --> 20
		for(var e = 0; e < 21; e++){
			// If i mod e === 0, then don't do anthing
			if((i % e) == 0){

				// Else if it does then set it to false
			} else {
				found = false;
				break;
			}
		}
		// If it's never set to false, then log it and break
		if(found == true){
			console.log(i);
			break;
		}
	}
};

smallest();