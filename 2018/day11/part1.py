#!/usr/bin/python3

# p_input = 3031
p_input = 3031
def calculate(x, y):
    rack_id = x + 10
    power_level = rack_id * y
    power_level += p_input
    power_level *= rack_id
    power_level = power_level // 100
    power_level %= 10
    power_level -= 5
    return power_level

def get_total(x, y, puzzle):
    if x + 3 >= 300 or y + 3 >= 300:
        print("Out of range")
        return -100
    else:
        total = 0
        for i in range(x, x+3):
            for j in range(y, y+3):
                total += puzzle[i][j]
        return total



full_puzzle = [[calculate(i+1, j+1) for j in range(300)] for i in range(300)]

result = { 'x': 1, 'y': 1 , 'total': get_total(0, 0, full_puzzle)}
total = -10
for x in range(297):
    for y in range(297):
        total = get_total(x, y, full_puzzle)
        if total > result['total']:
            result['total'] = total
            result['x'] = x + 1
            result['y'] = y + 1




print(result)
