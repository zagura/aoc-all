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
        new_limits = {'red': 0, 'green': 0, 'blue': 0}
        for r in all_rounds.split(';'):
            hand = {}
            colors = r.split(',')
            for c in colors:
                info = c.strip().split(' ')
                # print(info)
                hand[info[1]] = int(info[0])
            for c in hand:
                if hand[c] > new_limits[c]:
                    new_limits[c] = hand[c]
        power = 1
        for c in new_limits:
            power *= new_limits[c]
        print(f"{line[:-1]} : {new_limits} -> {power}")
        sum_ids += power
            # print(f"{game_id}: {hand}")
print(f"Task 1: {sum_ids}")
