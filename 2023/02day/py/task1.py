#!/usr/bin/python3

from sys import argv
if len(argv) > 1:
    in_file = argv[1]
else:
    in_file = 'input.in'

limits = { 'red': 12, 'green': 13, 'blue': 14 }
sum_ids = 0
with open(in_file, 'r', encoding='utf-8') as data:
    for line in data:
        if len(line) < 2:
            continue
        game, all_rounds = line.split(':')
        game_id = int(game.split()[1])
        add_value = game_id
        for r in all_rounds.split(';'):
            hand = {}
            colors = r.split(',')
            for c in colors:
                info = c.strip().split(' ')
                # print(info)
                hand[info[1]] = int(info[0])
            for c in hand:
                if hand[c] > limits[c]:
                    add_value = 0
                    break
        print(f"{line} -> {add_value}, {game_id}, {sum_ids}")
        sum_ids += add_value
            # print(f"{game_id}: {hand}")
print(f"Task 1: {sum_ids}")


