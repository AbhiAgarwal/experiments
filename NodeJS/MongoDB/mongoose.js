// Testing Connection
// Starting Connection to the MongoDB Database
var db = mongoose.connection;

// Error In the Communication
db.on('error', console.error.bind(console, 'Connection Error:'));

// Connection has been Established
db.once('open', function(){
  console.log("Connection Established");
});

// Variable Decleration
var mongoose = require('mongoose');
mongoose.connect('mongodb://');

// Schema Decleration
var tvshowSchema = mongoose.Schema({
    name: String,
    description: String,
    imageURL: String
});

// Model Decleration
var tvShow = mongoose.model('shows', tvshowSchema);

// Retrieving all TV Shows
tvShow.find(function(err, shows){
	if(err) console.log(err);
	console.log(shows[0].name);
	mongoose.connection.close();
});

// Declaring a new TV Show
var BigBangTheory = new tvShow({ 
	name: 'The Big Bang Theory',
	description: ' A woman who moves into an apartment across the hall from two brilliant but socially awkward physicists shows them how little they know about life outside of the laboratory.',
	imageURL: 'http://ia.media-imdb.com/images/M/MV5BMjQzMTYyODM4M15BMl5BanBnXkFtZTcwMTAxMDU1MQ@@._V1_SY317_CR10,0,214,317_.jpg'
});

// Saving TV Show into the Database
BigBangTheory.save(function (err, bigbang) {
  if (err) console.log(err);
  console.log("Done!");
});
