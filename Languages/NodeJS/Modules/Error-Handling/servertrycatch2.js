// Possible to catch the error when it isnt being deffered
 
try{
	throw new Error('Here');
} catch(e){
	console.log(e);
}