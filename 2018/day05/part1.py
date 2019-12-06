#!/usr/bin/python3

polymer = open('input.in').read()

polymer_next = []
changes = False
polymer = list(polymer[:-1])
while(True):
    changes = False 
    for index in range(len(polymer) - 1):
        l = polymer[index]
        r = polymer[index+1]
        if l and r:
            if l.lower() == r.lower() and l != r:
                polymer[index] = None
                polymer[index+1] = None
                changes = True
    polymer_next = list(filter(None, polymer))
    print("Length: {}.".format(len(polymer_next)))
    polymer = polymer_next
    if not changes:
        break

print(polymer)
print(len(polymer))
