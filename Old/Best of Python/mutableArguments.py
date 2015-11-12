def a(x = []):
	x.append(1)
	print x

def b(x = None):
	if x is None:
		x = []
	x.append(1)
	print x

# Comparing 'a()' to 'b()'
# appends 1 to the same array each time
a()
a()
a()

# creates array each time
b()
b()
b()

# Sources
# http://stackoverflow.com/questions/101268/hidden-features-of-python#11319