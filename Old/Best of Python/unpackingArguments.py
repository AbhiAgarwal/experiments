# You can send in arguments without parsing them inside the function.

def func(x, y):
	print x, y

a = (2, 3) # tuple
b = {'x': 2, 'y': 3} # dictionary
c = [2, 3] # lists

func(*a)
func(*b) # thats 'x' or 'y'
func(**b) # thats '2' or '3'
func(*c)

# which would be easier than doing either:
# b.x & b.y or a[0] & a[1] or c[0] & c[1] when using
# print(a) or print(b)

# Sources
# http://stackoverflow.com/questions/101268/hidden-features-of-python#111176