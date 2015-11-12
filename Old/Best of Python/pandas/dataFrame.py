# DataFrame

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from urllib2 import urlopen
from StringIO import StringIO

print 'DataFrame' + '\n'

'''
A DataFrame is a tablular data structure comprised 
of rows and columns, akin to a spreadsheet, database 
table, or R's data.frame object. You can also think 
of a DataFrame as a group of Series objects that 
share an index (the column names).
'''

data = {'year': [2010, 2011, 2012, 2011, 2012, 2010, 2011, 2012],
        'team': ['Bears', 'Bears', 'Bears', 'Packers', 'Packers', 'Lions', 'Lions', 'Lions'],
        'wins': [11, 8, 10, 15, 11, 6, 10, 4],
        'losses': [5, 8, 6, 1, 5, 10, 6, 12]}
football = pd.DataFrame(data, columns = ['year', 'team', 'wins', 'losses'])
print str(football) + '\n'

'''
Reading a CSV is as simple as calling the read_csv 
function. By default, the read_csv function expects 
the column separator to be a comma, but you can 
change that using the sep parameter.
'''

from_csv = pd.read_csv('./data/mariano-rivera.csv')
print str(from_csv.head()) + '\n'

'''
Our file had headers, which the function inferred 
upon reading in the file. Had we wanted to be more 
explicit, we could have passed header = None to the 
function along with a list of column names to use:
'''

cols = ['num', 'game', 'date', 'team', 'home_away', 'opponent',
        'result', 'quarter', 'distance', 'receiver', 'score_before',
        'score_after']
no_headers = pd.read_csv('./data/peyton-passing-TDs-2012.csv', 
						sep = ',', 
						header = None,
                        names = cols)
print no_headers.head()

'''
pandas various reader functions have many parameters 
allowing you to do things like skipping lines of 
the file, parsing dates, or specifying how to handle 
NA/NULL datapoints.
'''

# There's also a set of writer functions for 
# writing to a variety of formats
# no_headers.to_csv('./data/check.csv')

'''
Know who hates VBA? Me. I bet you do, too. Thankfully, 
pandas allows you to read and write Excel files, so 
you can easily read from Excel, write your code in 
Python, and then write back out to Excel - no need for VBA.
'''
# Reading Excel files requires the xlrd library. 
# You can install it via pip (pip install xlrd).
# Let's first write a DataFrame to Excel

football.to_excel('./data/football.xlsx', index = False)

del football

# Reading Excel using read_excel

football = pd.read_excel('./data/football.xlsx', 'sheet1')

print str(football) + '\n'

'''
We can also use the Python's StringIO library to 
read data directly from a URL. StringIO allows 
you to treat a string as a file-like object.
'''

# from urllib2 import urlopen
# from StringIO import StringIO

# store the text from the URL response in our url variable
url = urlopen('https://raw.github.com/gjreda/best-sandwiches/master/data/best-sandwiches-geocode.tsv').read()
from_url = pd.read_table(StringIO(url), sep = '\t')
print from_url.head(3)

# Source
# http://www.gregreda.com/2013/10/26/working-with-pandas-dataframes/