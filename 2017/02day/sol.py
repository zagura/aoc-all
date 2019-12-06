#!/usr/bin/python3

import sys

lines = sys.stdin.readlines()

#print("Read lines finished!")

fullsum = 0
for l in lines:
    vals = l.strip().split('\t')
#    print(vals)
    vals2 = list(map(lambda x: int(x), vals))
#    print(vals2)
    diff = max(vals2) - min(vals2)
    fullsum += diff

print(fullsum)
