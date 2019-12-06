#!/usr/bin/python3

import sys

fname = 'example.in'
if len(sys.argv) > 1:
    fname = sys.argv[1]

lines = open(fname).readlines()

x_min = 500
x_max = 500
y_min = 500
y_max = 0
all_clay = []

def print_well(puzzle):
    for row in puzzle:
        line = ''.join(row)
        print(line)

for l in lines:
    l = l.split(', ')
    if len(l) == 2:
        col1 = l[0].split('=')[1].split('..')
        col2 = l[1].split('=')[1].split('..')
        if l[0][0] == 'x':
            xs = col1
            ys = col2
        else:
            xs = col2
            ys = col1

        x = list(range(int(xs[0]), int(xs[-1]) + 1))
        y = list(range(int(ys[0]), int(ys[-1]) + 1))
        print(x)
        print(y)
        y_max = max(y + [y_max])
        y_min = min(y + [y_min])
        x_min = min(x + [x_min])
        x_max = max(x + [x_max])
        all_clay.append((x, y))

x_min -= 1
x_max += 1
y_max += 1
print("x: min({}), max({})\t y: min({}), max ({})".format(x_min, x_max, y_min, y_max))

puzzle = [['.' for x in range(x_min, x_max)] for y in range(y_min, y_max + 1)]

for (clay_x, clay_y) in all_clay:
    for x in clay_x:
        for y in clay_y:
            puzzle[y - y_min][x - x_min] = '#'

current_coordinates = (500 - x_min, y_min)
level = y_min - 1
water = [current_coordinates[0]]
while level < y_max:
    new_water = []
    next_level = level
    for x in water:
        if puzzle[level][x] == '.':
            puzzle[level][x] = '|'
            next_level = level + 1
            new_water.append(x)
        elif puzzle[level][x] == '#' or puzzle[level][x] != '.':
            level -= 1
            x_left = x - 1
            x_right = x + 1
            while puzzle[level + 1][x_left] != '.' and puzzle[level][x_left] != '#':
                puzzle[level][x_left] = '~'
                x_left -= 1
            while puzzle[level + 1][x_right] != '.' and puzzle[level][x_right] != '#':
                puzzle[level][x_right] = '~'
                x_right += 1
            next_level = level - 1
            if puzzle[level + 1][x_right] == '.':
                new_water.append(x_right)
                next_level = level + 1
            if puzzle[level + 1][x_left] == '.':
                new_water.append(x_left)
                next_level = level + 1
            if len(new_water) == 0:
                new_water = [x]
    level = next_level
    water = new_water
    print_well(puzzle=puzzle)
    print(level)

    

'''

while current_coordinates[1] < y_max:
    (x, y) = current_coordinates
    if puzzle[y + 1][x] == '.':
        puzzle[y + 1][x] = '|'
        y += 1
        current_coordinates = (x, y + 1)
    elif puzzle[y + 1][x] == '#':
        # Make water wider
        x_left = x - 1
        while x_left != '#':
            if puzzle[y + 1][x_left] = '#':
                puzzle[y][x_left] = '~'
                x_left -= 1
            x_right = x + 1
        while x_right != '#':
'''









