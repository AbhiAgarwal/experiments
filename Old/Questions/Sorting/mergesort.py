array_x = [88, 12, 78, 87, 89, 95, 16, 82]

def msort3(x):
    result = []
    if len(x) < 2:
        return x
    mid = int(len(x)/2)
    print 'Calling Mergesort(1/2*n, Data[1...n]) with first half of data'
    y = msort3(x[:mid])
    print 'Calling Mergesort(n, Data[1/2...n]) with second half of data'
    z = msort3(x[mid:])
    i = 0
    j = 0
    while i < len(y) and j < len(z):
            if y[i] > z[j]:
                result.append(z[j])
                j += 1
            else:
                result.append(y[i])
                i += 1
    result += y[i:]
    result += z[j:]
    print result
    return result

if __name__ == '__main__':
    result = msort3(array_x)
    print result