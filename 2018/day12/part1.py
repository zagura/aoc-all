#!/usr/bin/python3

total_generations = 20 
# fname = 'example.in'
fname = 'input.in'
lines = open(fname).readlines()
initial = lines[0].split()[2]
neighbour = 2

class Rule(object):
    def __init__(self, row):
        row = row.split(' => ')
        self.before = row[0]
        self.after = row[1].split('\n')[0]
    def __repr__(self):
        return str(self.__dict__)

rules = []
for line in lines[2:]:
    rules.append(Rule(line))

prefix = (total_generations + 1)*2*'.'
start_number = -1 * len(prefix)

initial = prefix + initial + prefix
# print(initial)
# print(rules)

def generation(state, ruleset):
    new_state = list(state)
    for i in range(neighbour, len(state) - neighbour):
        change = False
        for r in ruleset:         
            if state[i - neighbour: i + neighbour + 1] == r.before:
                # print("Applying rule: {} => {}".format(r.before, r.after))
                new_state[i] = r.after
                change = True
        if not change:
            new_state[i] = '.'

    new_state = ''.join(new_state)
#    print(state)
#    print(new_state)
#    print('---------------------------')
    return new_state

current_state = initial
for i in range(total_generations):
    current_state = generation(current_state, rules)

total_sum = 0
for i in range(len(current_state)):
    if current_state[i] == '#':
        total_sum += (start_number + i)
        print(start_number + i)

print(current_state)
print(len(current_state))
print("Sum: {}".format(total_sum))

