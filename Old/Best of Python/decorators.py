# allow to wrap a function or method in another function that can add 
# functionality, modify arguments or results, etc. You write decorators 
# one line above the function definition, beginning with an "at" sign (@).

def print_arguments(function):
	def wrapper(*args, **kwargs):
		print 'Arguments:', args, kwargs
		return function(*args, **kwargs)
	return wrapper

@print_arguments # calling decorator
def write(text):
	print text

write('hello')

# Sources
# http://simeonfranklin.com/blog/2012/jul/1/python-decorators-in-12-steps/