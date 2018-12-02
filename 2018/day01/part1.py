#!/usr/bin/python

lines = open('input1.in').readlines()

total_sum = 0

for l in lines:
    num = int(l)
    total_sum += num

print(total_sum)
