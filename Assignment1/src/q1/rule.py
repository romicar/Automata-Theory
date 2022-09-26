
"""
Created on Thu September 1 12:05:13 2022
@author: romica
"""

def printListofLists(myList):
    for i in range(1, n+1, 1):
        for j in range(1, m+1, 1):

            if(bool(myList[i][j])):
                print("X", end='')
            else:
                print("O", end='')
        print('\n', end='')


def writeToFile(myfile, myList):
    for i in range(1, n+1, 1):
        for j in range(1, m+1, 1):
            if(bool(myList[i][j])):
                myfile.write("X")
            else:
                myfile.write("O")
        myfile.write('\n')


def rule(a, b, c, d, e, f, g, h, i):
    if(b == 1):
        return 1
    else:
        return 0


def convertListToString(st):

    str1 = ""
    for ele in st:
        str1 += ele
    return str1


def Cloning(li1):
    li_copy = li1[:]
    return li_copy


myList = []  # empty list
sum = 0  # for total iterations

inputfile = open("config.txt", mode='r', encoding='utf-8')
# print(inputfile.readline())
text = inputfile.readline()
# print(inputfile.readline())
str = convertListToString(text)
for i in str.split():
    myList.append(int(i))
inputfile.close()

m = myList[0]
n = myList[1]
noOfInitialCells = myList[2]


new_m = m+2
new_n = n+2
original = [0] * new_n  # create a list of n+2 zeroes
# print(original)
for i in range(new_n):
    original[i] = [0] * new_m  # list a[i] is a list of m+2 zeroes
    # print(original[i])


c = [0] * noOfInitialCells
# print("**********")
# print(c)

# noOfInitialCells = myList[2]

# print(m)
# print(n)
# print("**********")

for i in range(noOfInitialCells):
    c[i] = [0] * 2  # list c[i] is a list of 2 zeroes
    # print(c[i])



new = [0] * new_n
# print("**********")

# print(new_a)
for i in range(new_n):
    new[i] = [0] * new_m

# initialize the entire matrix to zero
for i in range(n):
    for j in range(m):
        original[i][j] = 0
       # print(a[i][j])

inputfile = open("config.txt", mode='r', encoding='utf-8')
inputfile.readline()

for i in range(noOfInitialCells):
    list = inputfile.readline()
    str = convertListToString(list)
    k = 0
   
    for j in str.split():
        c[i][k] = int(j)
        # print(c[i][x])
        k = k+1

inputfile.close()

for i in range(noOfInitialCells):  # set the initial cells to 1
    original[n-c[i][1]+1][c[i][0]] = 1
    # print(n-c[i][1]+1)
    # print(c[i][0])

print("Initial state of the cullular automata :")
printListofLists(original)


while(1):
    print("Enter the number of iterations from previous state: ", end='')
    noOfItr = input()
    if (int(noOfItr) == -1):
        exit()

    new = Cloning(original)  # copying original into new

    for p in range(int(noOfItr)):
        for i in range(1, n+1, 1):

            for j in range(1, m+1, 1):
                outputrule = rule(original[i][j], original[i][(j-1)], original[(i)][(j+1)], original[(i-1)][(j)], original[(i+1)][(j)], original[(i-1)][(j-1)],  original[(i-1)]
                           [(j+1)],   original[(i+1)][(j+1)], original[(i+1)][(j-1)])
                if(bool(outputrule)):  # if left cell is 1
                    new_m = i  # update
                    new_n = j  # update
        new[new_m][new_n] = 1
        newfile = open("output.txt", mode='w', encoding='utf-8')
        writeToFile(newfile, new)
        newfile.close()
        original = Cloning(new)
    newfile = open("output.txt", mode='w', encoding='utf-8')
    writeToFile(newfile, new)
    print("Iteration no: ", end='')

    sum = sum+int(noOfItr)
    print(sum)
    print('\n', end='')
    printListofLists(new)
    newfile.close()
