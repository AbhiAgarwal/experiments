// Process On Exit

process.on('exit', function() {
  setTimeout(function() {
    console.log('This will not run');
  }, 0);
  console.log('About to exit.');
});
