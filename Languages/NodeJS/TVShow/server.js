var express = require('express'),
app = express(),
shows = require('./routes/shows');

app.configure(function(){
	app.use(express.logger('dev'));
	app.use(express.bodyParser());
});

app.get('/', shows.getAll);
app.get('/shows', shows.findAll);
app.get('/shows/:id', shows.findById);
/*
app.post('/shows', shows.addShow);
app.put('/shows/:id', shows.updateShow);
app.delete('/shows/:id', shows.deleteShow);
*/

app.listen(3000);
console.log("Listening on port 3000");