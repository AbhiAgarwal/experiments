// Emits Event MANY times

var EventEmitter = require('events').EventEmitter,
a = new EventEmitter;

a.on('event', function(){
	console.log('Event Called');
});

a.emit('event');