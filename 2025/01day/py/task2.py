import sys

input_file = '../input.in'
if len(sys.argv) > 1:
    input_file = sys.argv[1]

zeros = 0
passes = 0
last_left = False
with open(input_file, 'r', encoding='utf-8') as f:
    position = 50
    for line in f.readlines():
        sline = line.strip()
        if len(sline) == 0:
            continue
        direction = sline[0]
        count = int(sline[1:])
        prev = position
        pass_diff = 0
        prev_left = last_left
        print(f"{direction}: {count}")
        if direction == 'L':
            pass_diff = (position - count) // 100
            position = (position - count) % 100
            pass_diff *= -1
            # if last_zero:
            #     passes -= 1
            last_left = True
        elif direction == 'R':
            last_zero = False
            pass_diff += (position + count) // 100
            position = (position + count) % 100
            last_left = False
        if position == 0:
            zeros += 1
        if prev == 0:
            if last_left == True and prev_left == False:
                passes -= 1
            elif last_left == False and prev_left == True:
                passes += 1
        passes += pass_diff
        c = '+' if direction == 'R' else '-'
        print(f"Passes: {passes}, 0s: {zeros}, {c}{pass_diff}, position: {prev} -> {position}, {position - count}, {position + count}")

print(f"Task 1 result: {zeros}")
print(f"Task 2: {passes}")

