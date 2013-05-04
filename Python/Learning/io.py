def foo():
	factor = 10
	try:
		f = open('data.txt', 'w')
	except IOError as e:
		print 'file open error:', e
		return

	for i in range(0, 10, 1):
		print >> f, i*factor
		if i % 2 == 0:
			print >> f, 'even'
		else:
			print >> f, 'odd'
	f.close()