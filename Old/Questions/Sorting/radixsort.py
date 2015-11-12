from math import log
 
def getDigit(num, base, digit_num):
    # pulls the selected digit
    return (num // base ** digit_num) % base  
 
def makeBlanks(size):
    # create a list of empty lists to hold the split by digit
    return [ [] for i in range(size) ]  
 
def split(a_list, base, digit_num):
    buckets = makeBlanks(base)
    for num in a_list:
        # append the number to the list selected by the digit
        buckets[getDigit(num, base, digit_num)].append(num)
    print 'Splitting: ', buckets 
    return buckets
 
# concatenate the lists back in order for the next step
def merge(a_list): 
    new_list = []
    for sublist in a_list:
       new_list.extend(sublist)
    print 'Merged: ', new_list 
    return new_list
 
def maxAbs(a_list):
    # largest abs value element of a list
    return max(abs(num) for num in a_list)  
 
def radixSort(a_list, base):
    # there are as many passes as there are digits in the longest number
    passes = int(round(log(maxAbs(a_list), base)) + 1) 
    print 'Number of passes:', passes
    new_list = list(a_list)
    for digit_num in range(passes):
        print 'Call', (str(digit_num) + ':')
        new_list = merge(split(new_list, base, digit_num))
        print new_list
    return new_list

if __name__ == '__main__':
    result = radixSort([88, 12, 78, 87, 89, 95, 16, 82, 100], 10)