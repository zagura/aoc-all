import sys

input_file = '../input.in'
if len(sys.argv) > 1:
    input_file = sys.argv[1]

zeros = 0

with open(input_file, 'r', encoding='utf-8') as f:
    position = 50
    for line in f.readlines():
        sline = line.strip()
        if len(sline) == 0:
            continue
        direction = sline[0]
        count = int(sline[1:])
        print(f"{direction}: {count}")
        if direction == 'L':
            position = (position - count) % 100
        elif direction == 'R':
            position = (position + count) % 100
        if position == 0:
            zeros += 1

print(f"Task 1 result: {zeros}")

