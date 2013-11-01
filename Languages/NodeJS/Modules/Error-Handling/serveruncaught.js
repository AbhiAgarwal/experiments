var http = require('http')

http.createServer(function(){
	throw new Error('Uncaught');
}).listen(8888);

	/*
		This Displays:

		throw new Error('Uncaught');
		Error: Uncaught
   		at Server.<anonymous> (/Users/Abhi/Desktop/NodeJS/Error-Handling/server.js:4:8)
	 */

	// Node will behave this way because the state of the process
	// after an uncaught exception is uncertain.
	// This may work or may not work after an error is unhandled.
