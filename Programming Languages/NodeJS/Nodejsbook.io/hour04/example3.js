var breakfast = function(food, drink, callback){
	console.log("I like:", food, "and", drink);
	if(callback && (typeof(callback) === 'function')){
		callback();
	}
}

breakfast("Burger", "Coke", function(){
	console.log("I just finished eating it");
});