class BoundedQueue(object):
	# Initialize the Variables, and set the Length
	# @Param: length of the queue;
	# @Return: none;
	def __init__(self, length):
		super(BoundedQueue, self).__init__()
		# Checks it the Queue size is 0
		self.queue = [None] * length
		self.head = 0
		self.tail = 0
		self.size = 0
	# Check if the Queue is empty (Support Function)
	# @Param: none;
	# @Return: none;
	def isEmpty(self):
		return True if (self.size == 0) else False
	# Check if the Queue is full (Support Function)
	# @Param: none;
	# @Return: none;
	def isFull(self):
		return True if (self.size == len(self.queue)) else False
	# Insert an element into the Queue
	# @Param: n, an integer to put into the Queue
	# @Return: none;
	def enqueue(self, n):
		if len(self.queue) == 0: return 'Size of Queue is Zero'
		if self.isFull(): return 'Queue is full'
		elif isinstance(n, int):
			if(self.tail == len(self.queue)): self.tail = 0
			self.queue[self.tail] = n
			self.tail += 1
			self.size += 1
		else: return 'entered number is not an integer'
		return
	# Take out an element from the Queue
	# @Param: none;
	# @Return: the integer that was dequeued
	def dequeue(self):
		toReturn = None
		if len(self.queue) == 0: return 'Size of Queue is Zero'
		if self.isEmpty(): return 'Queue is empty'
		else:
			if(self.head == len(self.queue)): self.head = 0
			toReturn = self.queue[self.head]
			self.head += 1
			self.size -= 1
		return toReturn
