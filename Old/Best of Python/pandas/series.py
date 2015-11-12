# Series

'''
pandas introduces two new data structures to Python - 
Series and DataFrame, both of which are built on top of NumPy
'''
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

pd.set_option('max_columns', 50)

print 'Series' + '\n'

'''
A Series is a one-dimensional object similar to an array, 
list, or column in a table. It will assign a labeled index 
to each item in the Series. By default, each item will 
receive an index label from 0 to N, where N is the 
length of the Series minus one.
'''

# create a Series with an arbitrary list
s = pd.Series([7, 'Heisenberg', 3.14, -1789710578, 'Happy Eating!'],
	index = ['A', 'B', 'C', 'D', 'E'])
print str(s) + '\n'

'''
You can also use dictionaries, and the data structure will also
list them alphabetically for you. If you want a NaN then just
make the integer/string value: None.
'''

d = pd.Series({'hello': 2000, 'bye': 3000, 'seya': None})
print str(d) + '\n'

'''
As it is a dictionary you can do:
'''

print str(d[['hello']]) # or
print str(d[1]) + '\n' # 'hello' as it is alphabetically sorted

'''
Filtering data is also very easy
-> d < 3000 returns a Series of True/False values, 
which we then pass to our Series d, 
returning the corresponding True items
'''

print str(d[d < 3000]) + '\n' # Returns [False, True]
print str(d < 3000) + '\n' # Check like this

# Change values like this

d[d >= 3000] = 2999
print str(d) + '\n'

# Mathematical operations can be done using scalars and functions.

print str(d / 3) + '\n'
print str(np.square(d)) + '\n'

# Comparing two lists and then adding values of them:
# Similar ones will have values
# Non similar ones will be NaN

print str(d[['hello', 'bye']] + d[['hello']]) + '\n'

# check if the values are not null or are null

print str(d.notnull()) + '\n'
print str(d.isnull())

# Source
# http://www.gregreda.com/2013/10/26/intro-to-pandas-data-structures/