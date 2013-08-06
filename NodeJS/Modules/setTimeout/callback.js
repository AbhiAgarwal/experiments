// Testing Callback
// Console log Example

setTimeout(function() {
	console.log("Callback has occured");	
}, 1000);

console.log("Hello");

setTimeout(function() {
	console.log("Bye");
}, 1000);

console.log("World");