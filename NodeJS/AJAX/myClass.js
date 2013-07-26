var EventEmitter = process.EventEmitter,
myClass = function() {};
myClass.prototype.__proto__ = EventEmitter.prototype;

var a = new myClass;
a.on('some event', function() {
	console.log("Some Event");
});

a.emit('some event');