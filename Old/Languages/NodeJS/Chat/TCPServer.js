var net = require('net');
var ChatServer = net.createServer();

ChatServer.on('connection', function(client){
	// Sends client a Greeting when connected
	client.write('Hello\n');
	client.on('data', function(data){
		// Converts what the client says to String
		console.log(data.toString());
	});

});

ChatServer.listen(9000);