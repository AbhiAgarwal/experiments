"use strict";
/*
* Module Decleration
*/
var net = require('net');

// Variable Decleration
var chatServer = net.createServer(),
clientList = [];

// Chat server is on
chatServer.on('connection', function(client){
	// Solves problem in TCPServer3.js
	client.name = client.remoteAddress + ':' + client.remotePort
	for(int i = 0; i < clientList.length; i++){
		if(clientList[i].contains(client.remoteAddress + ':' + client.remotePort)){
			client.name += ' number' + i;
		}
		else {
			client.name = client.remoteAddress + ':' + client.remotePort;
		}
	}
	// Greeting & Pushing client onto clientList array
	client.write('Hi ' + client.name + '!\n');
	clientList.push(client);

	// When client sends data to the server & other users
	client.on('data', function(data){
		broadcast(data, client);
	});

	// When a Client ends the session
	client.on('end', function() {
		clientList.splice(clientList.indexOf(client), 1);
	});

	// Error Logging
	client.on('error', function(e){
		console.log(e);
	});
});

// Broadcasting the message to everyone but the User
function broadcast(message, client){
	var cleanup = [];
	for(var i = 0; i < clientList; i++){
		if(client !== clientList[i]){
			if(clientList[i].writable){
				clientList[i].write(client.name + " says " + message);
			}
			else{
				// Error Checking
				cleanup.push(clientList[i]);
				clientList[i].destroy();
			}
		}
	}
	for(var i = 0; i < cleanup.length; i++){
		clientList.slice(clientList.indexOf(cleanup[i]), 1);
	}
}

// Starts server at port 9000
chatServer.listen(9000);