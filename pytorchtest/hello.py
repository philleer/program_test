#!/usr/bin/env python
import first

laugh_test = first.Person()
for i in range(3):
    laugh_test.laugh()

def square_sum(a, b):
    c = a**2 + b**2
    return a,b,c

def int_inc(b):
    b[0] = b[0] + 1
    return b

def leap_year(year):
    if year%400 == 0 or (year%100 != 0 and year%4 == 0):
        print "%d is leap year!" %year
        return True
    else:
        print "%d is not leap year!" %year
        return False

class Bird(object):
    have_feature = True
    birth = 'egg'
    way_of_move = 'fly'

    def move(self, dx, dy):
        position = [0,0]
        position[0] = position[0] + dx
        position[1] = position[1] + dy
        return position
class Chicken(Bird):
    way_of_move = 'walk'

class Human(object):
    laugh = "hahahaha"
    age = 0
    name = ['li', 'lei']

    def show_laugh(self):
        print self.laugh

    def show_100laugh(self):
        for i in range(100):
            print self.laugh

    def __init__(self, mode_gender):
        self.gender = mode_gender

    def printgender(self):
        print self.gender

class superList(list):
    def __sub__(self, b):
        a = self[:]
        b = b[:]

        while len(b)>0:
            element_b = b.pop()
            if element_b in a:
                a.remove(element_b)
        return a

summer = Chicken()
print 'after move: ', summer.move(5,5)

ming = Human('male')
hong = Human('female')
ming.age = 18
print ming.age, hong.age

ming.name[0] = 'zhang'
print ming.name, hong.name

print superList([2,4,3]) - superList([2,3])

f = open("data.txt", "w")
# f.write('I like apple'+"\n")
# f.write('tom, 12, 86'+"\n")
# f.write('lee, 15, 99'+"\n")
# f.write('lucy, 11, 58'+"\n")
# f.write('joseph, 19, 56'+"\n")
f.write("I like apple")
f.write("tom, 12, 86")
f.write("lee, 15, 99")
f.write("lucy, 11, 58")
f.write("joseph, 19, 56")
f.write('''
first line
seconde line
third line
''')
f.close()

# f = open("data.txt", "r")
# for line in f:
#     print line, f.tell()

# print '%c' %f.tell()

# print f.readline()
# contend = f.read(12)
# print contend[:]
# print f.readlines()[0]
# f.close()

def func(a, b = 33, c = 44):
    print a, b, c

# temp_args = (1, 3, 4)
# func(temp_args)
# func(*temp_args)

# S = 'abdfhij'
# for i in range(0, len(S), 2):
#     print S[i]
# for (index, char) in enumerate(S):
#     print index, char
print map((lambda x,y: x+y), [1,2,3], [6,7,8])
raise StopIteration
raise StopIteration()

