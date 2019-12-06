#!/usr/bin/python

lines = open('input2.in').readlines()

total_sum = 0
input_lines = []
history = {0, }
found_flag = False
found_val = 0
for l in lines:
    num = int(l)
    input_lines.append(num)

while not found_flag:
    for l in input_lines:
        total_sum += l
        if total_sum in history:
#        for t in history:
#            if total_sum == t:
            found_flag = True
            found_val = total_sum
            break
        history.add(total_sum)

print(found_val)
print("Total elements: {}".format(len(history)))
