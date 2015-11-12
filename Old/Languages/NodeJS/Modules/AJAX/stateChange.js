var ajax = new XMLHTTPRequest;
ajax.addEventListener('stateChange', function(){
	if(ajax.readyState == 4 && ajax.responseText){
		alert('we got some data ' + ajax.responseText);
	}
});

ajax.open('GET', '/my-page');
ajax.send(null);