// Not possible to defer catching an error you throw in the future (pausing 10 seconds)

try{
	setTimeout(function() {
		throw new Error('Here');
	}, 10);
} catch(e){}