# To import another Python File and get its function is pretty simple
# Running file using importPythonFile.py file1(.py)
import sys
import os

def getFiles(fileNumber):
	fileOne = sys.argv[fileNumber]
	if ".py" in fileOne: fileOne = fileOne.replace(".py", "")
	fileOneImport = __import__(fileOne)
	fileOneFunction = '__name__'
	# This will ask the user for an input for the function to use
	# or if the user uses '__name__' == '__main__' then uses that
	if len(dir(fileOneImport)) != 5:
		fileOneFunction = raw_input("Main function for: " + fileOne + "? ")
		if fileOneFunction == '': fileOneFunction = '__name__'
	else:
		fileOneFunction = '__name__'
	# also print out the methods to choose from as we already
	# have the list..
	fileOneCall = getattr(fileOneImport, fileOneFunction) # gets function!
	if callable(fileOneCall):
		print 'Can Call'
		print fileOneCall()

def hello():
	return 'hello'

# Try it. This will get the function name, say input: hello
# and then say if it is able to call or not and then call it.

if __name__ == '__main__':
	getFiles(0)