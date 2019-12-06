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
    div = 0
    for v1 in vals2:
        for v2 in vals2:
            if v1 % v2 == 0:
                if v1 // v2 > div:
                    div = v1 // v2
    fullsum += div

print(fullsum)
