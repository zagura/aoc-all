#!/usr/bin/python

lines = open('input1.in').readlines()

twos = 0
threes = 0

for line in lines:
    d = dict()
    is_two = 0
    is_three = 0
    for c in line:
        if c in d:
            d[c] = d[c] + 1
        else:
            d[c] = 1
    for k in d:
        if d[k] == 2:
            is_two = 1
        elif d[k] == 3:
            is_three = 1
    twos += is_two
    threes += is_three

print("There are {} twos.".format(twos))
print("There are {} trees.".format(threes))
print("The checksum is {}.".format(twos*threes))
