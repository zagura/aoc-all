#!/usr/bin/python3

import sys
input_file = 'input0.in'
if len(sys.argv) > 1:
    input_file = sys.argv[1]
line = open(input_file).readlines()[0].split()
player_count, marble_count = int(line[0]), int(line[6])
marble_count *= 100
current_state = [0, 1]

last_marble = 1
player_no = 0
scores = {}
for round_no in range(2, marble_count + 1):
    player_no += 1
    player_no %= player_count
    if round_no % 30000 == 0:
        print(round_no)
    if round_no % 23 != 0:
        index = last_marble + 2 
        index = index % len(current_state)
        if index == 0:
            index = len(current_state)
        current_state = current_state[:index] + [round_no] + current_state[index:]
        last_marble = index
    else:
        temp_score = round_no
        index = last_marble - 7
        index %= len(current_state)
        temp_score += current_state[index]
        current_state = current_state[:index] + current_state[index+1:]
        last_marble = index
        if player_no not in scores:
            scores[player_no] = 0
        scores[player_no] += temp_score
#    print(current_state)
#    temp = [i for i in current_state]
#    temp[index] = -1
#    print(temp)
#    print(' ')

print("Scores:")
print(scores)
scores_list = list(scores.values())
scores_list.sort(reverse=True)
print("")
print(scores_list)
#scores_list.sort(key=lambda x: x[1])
