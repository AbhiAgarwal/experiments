// In Node everything runs on one thread, so when you run the page:
// 
// 	1. it displays "hello"
// 	2. it will set books to []
// 	3. refresh the page
// 	4. it won't display "hello" anymore

var http = require('http'), // calls the http library - sets it as "http" variable
books = [ // creates the book array
	'Hello',
	'Apple'
];

var server = http.createServer(function(req, res){ // declares the server using the http library
	res.writeHead(200); // writes header as 200
	res.end(books[0]); // prints the books[0] (Hello) 
	books = []; // sets books to nothing
}).listen(8888); // starts port on 8888