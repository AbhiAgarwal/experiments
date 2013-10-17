# Finds the missing term of arithmetic sequence
# Enter your code here. Read input from STDIN. Print output to STDOUT
import fileinput

def startfunction():
    # parsing the data
    file_input = fileinput.input()
    array = []
    for line in file_input:
        array.append(line)
    length = int(array[0].replace('\n', ''))
    array_values = map(int, array[1].split())
    
    # test case
    if length == 0:
        print 0
        return
    if length != len(array_values):
        length = len(array_values)
    
    # calculates the shortest value
    shortest = array_values[1] - array_values[0]
    for i in range(0, length - 1):
        if shortest > (array_values[i + 1] - array_values[i]):
            shortest = (array_values[i + 1] - array_values[i])
   
    # we now have the shortest sequence
    # now it is a missing number problem
    thinkLargest = array_values[0] + shortest
    change = 0
    for i in range(0, length - 1):
        if (array_values[i] + shortest) != array_values[i + 1]:
            thinkLargest = array_values[i] + shortest
            change += 1
    
    if change > 1:
        print Nil
    else:
        print thinkLargest
        return
    # it will not display the shortest
  
if __name__ == '__main__':
    startfunction()