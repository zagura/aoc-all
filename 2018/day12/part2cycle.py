#!/usr/bin/python3

total_generations = 50000000000 
#total_generations = 5000
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

prefix = 3*'.'
start_number = -1 * len(prefix)

initial = prefix + initial + prefix*8
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

def reduce_offset(offset, state):
    diff = 5
    for i in range(len(state)):
        if state[i] == '#':
#            print("Offset reduce at {}.".format(i))
            if i > diff:
                offset += (i - diff)
                state = ''.join(state[i-diff:])
#            print(state)
            return (offset, state)

current_state = initial
last_state = initial
cycle_generation = 0
offset = start_number


for i in range(total_generations):
    if i % 10000 == 0:
        print("Generation {}".format(i))
    if i % 20 == 0:
        (offset, current_state) = reduce_offset(offset, current_state)
        current_state = current_state + 20*'.'
    last_state = current_state 
    current_state = generation(current_state, rules)
#    print(last_state)
    if '.' + last_state[:-1] == current_state:
        cycle_generation = i + 1
#        print("Pattern fount at {} generation.".format(i))
#        break
    
total_sum = 0

for i in range(len(current_state)):
    if current_state[i] == '#':
        total_sum += i

print(current_state)
print(len(current_state))
print("Sum: {}".format(total_sum))

