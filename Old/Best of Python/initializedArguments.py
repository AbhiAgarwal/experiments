# Sometimes you don't have to pass in any arguments
# when you've intialized it inside the parameters:

def a(i = 2):
	print i
	i += 1

# It's the same each time, kind of like.
# So when the value is static (not changing) you can usually just
# declare it inside the parentheses
a()
a()
a()
# and when you want to change it from '2' you just do:
a(3)
# It's a neat feature so you have both the default value and the new value
# & you can make it blank when you want too

# When you're doing something like this:
def b(a = []):
	a.append(1)
	print a

# You've to be careful as the array actually never changes
# as you append to it, the next element would just append to the end of the array
# arrays will append each time.
b()
b()
b()
# and then you can just do
b(a=[]) # to reset it

# Check mutableArguments.py for more information