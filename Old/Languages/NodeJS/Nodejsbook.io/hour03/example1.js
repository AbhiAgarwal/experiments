var http = require('http'),
urls = ['abhiagarwal.com', 'google.com', 'yahoo.com'];

var fetchPage = function(url){
	var startTime = new Date();
	http.get({host: url}, function(res){
		console.log("Got Response from the URL: ", url);
		console.log("Time: ", new Date() - startTime, "ms");
	});
};

for(var i = 0; i < urls.length; i++){
  fetchPage(urls[i]);
}