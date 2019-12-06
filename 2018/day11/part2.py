#!/usr/bin/python3

serial = 3031
def calculate(x, y):
    rack_id = x + 10
    power_level = (rack_id * y) + serial
    power_level = (power_level * rack_id ) // 100
    power_level = (power_level % 10) - 5 
    return power_level

def get_total(x, y, puzzle, size):
    if x + size >= 300 or y + size >= 300:
        print("Out of range")
        return -100
    else:
        total = puzzle[x][y]['parts']
        for j in range(size - 1):
            total += puzzle[x + size - 1][y+j]['val']
            total += puzzle[x+j][y + size - 1]['val']
        total += puzzle[x + size - 1][y + size - 1]['val']
        puzzle[x][y]['parts'] = total
        return total



map_size = 300
full_puzzle = [[{'val': calculate(i + 1, j + 1), 'parts': 0} for j in range(map_size)] 
                    for i in range(map_size)]

for s in range(1, map_size + 1):
    result = { 'x': 1, 'y': 1 , 'total': get_total(0, 0, full_puzzle, s)}
    total = -10
    for x in range(300 - s):
        for y in range(300 - s):
            total = get_total(x, y, full_puzzle, s)
            if total > result['total']:
                result['total'] = total
                result['x'] = x + 1
                result['y'] = y + 1
    print("{} :: {}".format(s, result))

