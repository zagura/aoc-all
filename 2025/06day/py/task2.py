#!/usr/bin/python3
import sys

fname = 'input.in'
if len(sys.argv) == 2:
    fname = sys.argv[1]

with open(fname) as f:
    line = f.readlines()[0].split(',')


fishes = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
for n in line:
    fishes[int(n)] += 1

for d in range(256):
    zeros = fishes[0]
    for i in range(0,9):
        fishes[i] = fishes[i+1]
    fishes[6] += zeros
    fishes[8] += zeros
    print(f"Day {d}: {fishes}")

total = 0
for f in fishes:
    total += f
print(f"Total is {suma}")

