import time
import sys
from boundedQueue import BoundedQueue

# Runs & Initializes the BoundedQueue
if __name__ == '__main__':
	startTime = time.clock()
	# Test Cases
	# [[SIZE OF THE QUEUE], ELEMENTS IN THE QUEUE]
	testcases = [
		[[0], None],
		[[0], 1],
		[[1], 1],
		[[2], None],
		[[3], -1, 2, -100000],
		[[10], 1, 2, 3, 4, 5, 6, 7, 8, 9, 10],
		[[4], 90, 29, 30, 50],
		[[2], 40, 50, 60, 70],
		[[9], 120, 392, 293, 293, 293, 129, 291, 2039, 2930],
		[[0], 120, 3920, 3921, 293],
		[[-1], 120, 3920, 3921, 293],
	]
	# Expected Results
	# ['EXPECTED ERROR'] OR [DEQUEUED NUMBERS]
	expected = [
		['No Int'],
		['Size of Queue is Zero'],
		[1],
		['No Int'],
		[-1, 2, -100000],
		[1, 2, 3, 4, 5, 6, 7, 8, 9, 10],
		[90, 29, 30, 50],
		['Queue is full'],
		[120, 392, 293, 293, 293, 129, 291, 2039, 2930],
		['Size of Queue is Zero'],
		['Size of Queue is Zero'],
	]
	# Array to store the results
	results = [[] for i in range(0, len(testcases))]
	counter1 = 0
	# Runs the results and computes the outcome
	for i in testcases:
		print str(counter1 + 1) + '. Test on: ' + str(i)
		x = BoundedQueue(i[0][0])
		# Computers & Checks for errors in the Enqueues
		for m in i:
			if not isinstance(m, list):
				if isinstance(m, int):
					result = x.enqueue(m)
					if result == 'Size of Queue is Zero':
						results[counter1].append('Size of Queue is Zero')
					elif result == 'Queue is full':
						results[counter1].append('Queue is full')
				else:
					results[counter1].append('No Int')
		# Computes the dequeues
		for m in i:
			if [0] not in i:
				if not isinstance(m, list):
					if None not in i:
						results[counter1].append(x.dequeue())
		counter1 += 1
	counter1 = 0
	errors = 0
	# Computers the number of errors in the results
	for i in results:
		if expected[counter1] in i:
			errors += 1
			print 'Error: ' + str(i) + ' does not equal to ' + str(expected[counter1])
		counter1 += 1
	# Prints errors
	errorPercentage = float(errors) / float(counter1) * 100
	print "Number of results: " + str(counter1)
	print "Number of errors: " + str(errors)
	print "Percentage errors " + str(round(errorPercentage, 2)) + "%"
	print "The time taken to run " + str(counter1) + " cases is: " + str(time.clock() - startTime) + "s"
