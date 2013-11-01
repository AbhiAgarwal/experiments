var net = require('net'),
ChatServer = net.createServer(),
clientList = [];

ChatServer.on('connection', function(client){
	// Writes when Client connects
	client.write('Hello\n');
	// Pushes client into clientList
	clientList.push(client);
	// If a client sends data
	client.on('data', function(data){
		for(var i = 0; i < clientList; i++){
			console.log(data);
			clientList[i].write(data);
		}
	});
});

ChatServer.listen(9000);