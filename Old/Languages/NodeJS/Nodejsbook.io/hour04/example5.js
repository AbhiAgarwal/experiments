function sleep(m){
	var start = new Date().getTime();
	while((new Date().getTime() - start) < m);
}

function getPage(){
	console.log("Getting Page");
	sleep(2000);
	console.log("Got Page");
}

function getAPI(){
	console.log("Getting API");
	sleep(2000);
	console.log("Got API");
}

getPage();
getAPI();