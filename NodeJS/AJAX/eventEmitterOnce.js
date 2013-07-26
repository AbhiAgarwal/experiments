// Emits an event ONCE

var EventEmitter = require('events').EventEmitter,
a = new EventEmitter;

a.once('event', function(){
	console.log('Event Called');
});

a.emit('event');
a.emit('event');