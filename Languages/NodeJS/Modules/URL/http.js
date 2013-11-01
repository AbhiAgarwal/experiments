var http = require("http"), 
url = require("url"); 
 
http.createServer(function (request, response) { 
   request.on('end', function (){
      var getURL = url.parse(request.url, true).query; 
      response.writeHead(200, {
         'Content-Type': 'text/plain'
      }); 
      response.end('Here is your data: ' + getURL['data']); 
      console.log(getURL);
   }); 
}).listen(8080);