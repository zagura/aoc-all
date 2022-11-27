#!/usr/bin/python3
# Advent of Code 2020: Day 1
# Task 1: Found two numbers, which sums to 2020
lines = []
with open("input.in") as f:
    lines = [int(x) for x in f.readlines() if x != "\n"]

for i in range(len(lines) - 1):
    for j in range(i + 1, len(lines)):
        num1 = lines[i]
        num2 = lines[j]
        if num1 + num2 == 2020:
            print("Numbers: {} and {}".format(num1, num2))
            print("Multiply: {}".format(num1 * num2))
