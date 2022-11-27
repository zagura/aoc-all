#!/usr/bin/python3
# Advent of Code 2020: Day 1
# Task 2: Found three numbers, which sums to 2020
lines = []
with open("input.in") as f:
    lines = [int(x) for x in f.readlines() if x != "\n"]

for i in range(len(lines) - 2):
    for j in range(i + 1, len(lines) - 1):
        for k in range(j + 1, len(lines)):
            num1 = lines[i]
            num2 = lines[j]
            num3 = lines[k]
            if num1 + num2 + num3 == 2020:
                print("Numbers: {}, {} and {}".format(num1, num2, num3))
                print("Multiply: {}".format(num1 * num2 * num3))
