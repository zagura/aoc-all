#!/usr/bin/python3

polymer = list(open('input.in').read()[:-1])
letters = [chr(x) for x in range(ord('a'), ord('z') + 1)]
total = len(polymer)

def get_len(polymer):
    result_polymer = [' ', polymer[0]]
    for index in range(1, len(polymer)):
        r = polymer[index]
        l = result_polymer[-1]
        if l.lower() == r.lower() and l != r:
            result_polymer = result_polymer[:-1]
        else:
            result_polymer.append(r)
    return len(result_polymer[1:])

for l in letters:
    current_polymer = list(filter(lambda x: x.lower() != l, polymer))
    length = get_len(current_polymer)
    if length < total:
        total = length

print(total)
