var fs = require('fs'),
http = require('http');

http.get({host: 'abhiagarwal.com'}, function(res){
	console.log("Got a response for abhiagarwal.com");
}).on('error', function(e){
	console.log("Error:", e);
});

fs.readFile('example4file1.txt', 'utf8', function(err, data){
	if(err) {throw err;}
	console.log("Read File 1!");
});

http.get({host: 'google.com'}, function(res){
	console.log("Got response for google.com");
}).on('error', function(e){
	console.log("Error:", e);
});

fs.readFile('example4file2.txt', 'utf8', function(err, data){
	if(err) {throw err;};
	console.log("read File 2!");
});