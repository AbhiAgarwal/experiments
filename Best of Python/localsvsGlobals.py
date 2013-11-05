# Finding out the variables in the global vs local scope is 
# pretty easy in Python:

globalVariable = 5

def localVariable():
	local = 5
	print locals() # prints all local variables

print globals() # prints all global variables
localVariable()

# Sources
# http://simeonfranklin.com/blog/2012/jul/1/python-decorators-in-12-steps/