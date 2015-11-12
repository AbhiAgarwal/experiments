var start = Date.now();

setTimeout(function(){
	console.log(Date.now() - start);
	for(var i = 0; i < 1000000000; i++){}
}, 5000);

setTimeout(function(){
	console.log(Date.now() - start);
}, 10000);