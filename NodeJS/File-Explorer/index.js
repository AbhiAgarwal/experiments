/*
* Module dependencies
*/

var fs = require('fs'),
stdin = process.stdin,
stdout = process.stdout;

// Read Directory
fs.readdir(__dirname, function(err, files){
	console.log(files);
});

/*
fs.readdir(path, callback);

Asynchronous readdir(3). Reads the contents of a directory. 
The callback gets two arguments (err, files) where files is an 
array of the names of the files in the directory excluding '.' and '..'. 
*/

fs.readdir(process.cwd(), function(err, files){

/*
process.cwd();

Returns the current working directory of the process.
console.log('Current directory: ' + process.cwd());
*/

	console.log('');

	if(!files.length){
		return console.log('	\033[31m No files to show!\033[39m\n');
	}

	console.log('	Select which file or directory you want to see\n');

	var stats = [];

	function file(i){
		var filename = files[i];
		fs.stat(__dirname + '/' + filename, function(err, stat){
			stats[i] = stats;
			if(stats[Number(data)].isDirectory()){
				fs.readdir(__dirname + '/' + filename, function(err, files){
					console.log('');
					console.log('	('	+ files.length + ' files');
					files.forEach(function(file){
						console.log('	- 	' + file);
					});
					console.log('');
				});
			} else {
				fs.readFile(__dirname + '/' + filename, 'utf8', function(err, data){
					console.log('');
					console.log('\033[90m' + data.replace(/(.*)/g,	'	$1') + '033[39m');
				});
			}

			if(++i == files.length){
				read();
			}
			else{
				file(i);
			}

		});
	}

	function read(){
		console.log('');
		stdout.write('	\033[33mEnter your Choice: \033[39m');

		stdin.resume();
		stdin.setEncoding('utf8');
		stdin.on('data', option);
	}

	function option(data){
		var filename = files[Number(data)];
		if(!filename){
			stdout.write('	\033[31mEnter your choice: \033[39m');
		} else {
			stdin.pause();
			fs.readFile(__dirname + '/' + filename, 'utf8', function(err, data){
				console.log('');
				console.log('\033[90m' + data.replace(/(.*)/g, '	$1') + '\033[39m');
			});
		}
	}

	file(0);
});

