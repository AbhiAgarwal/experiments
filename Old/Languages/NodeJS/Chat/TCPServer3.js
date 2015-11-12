/*
* Module Decleration
*/
var net = require('net');

// Variable Decleration
var chatServer = net.createServer(),
clientList = [];

// Chat server is on
chatServer.on('connection', function(client){
	// allows you to have the same client name right now
	client.name = client.remoteAddress + ':' + client.remotePort;
	client.write('Hi ' + client.name + '!\n');
	clientList.push(client);
	client.on('data', function(data){
		broadcast(data, client);
		console.log(data.toString());
	});
});

function broadcast(message, client){
	for(var i = 0; i < clientList; i++){
		if(client !== clientList[i]){
			clientList[i].write(client.name + " says " + message);
			console.log(message);
		}
	}
}

chatServer.listen(9000);