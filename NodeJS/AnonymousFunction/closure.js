var displayClosure = function(){
	var count = 0;
	return function() {
		return ++count;
	};
};

var inc = displayClosure();
console.log(inc());
console.log(inc());
console.log(inc());