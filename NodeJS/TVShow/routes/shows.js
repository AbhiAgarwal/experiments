var MongoClient = require('mongodb').MongoClient,
MongoURL = 'mongodb://:',
ShowList = [];

MongoClient.connect(MongoURL, function(err, db) {
  	if(err) throw err;
  	db.collection('Shows', function(err, collection) {
  		collection.find().toArray(function(err, items) {
			ShowList = items;
		});
  	});
});

exports.getAll = function(req, res){
	res.send(ShowList);
};

exports.findAll = function(req, res){

	res.send([{name: 'show1'}, {name: 'show2'}, {name: 'show3'}]);
};

exports.findById = function(req, res){
	res.send({id: req.params.id, name: "The Name", description: "description"});
};