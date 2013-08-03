# What is the first term in the Fibonacci sequence to contain 1000 digits?

f1 = 1 # first term
f2 = 1 # second term
term = 3 # how many terms there are in the Sequence

while len(str(f1 + f2)) < 1000: # while the string length of (f1 + f2) is less than 1000
	f1, f2 = f2, f1 + f2 # set f1 to f2, and set f2 to f1 + f2
	term += 1 # add another term

print term # print the term