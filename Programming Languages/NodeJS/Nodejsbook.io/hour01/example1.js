var http = require('http');
http.createServer(function(req, res){
	res.writeHead(200, {'Content-Type': 'plain/text'});
	res.end('Hello World\n');
}).listen(8888);
console.log('Server Started');