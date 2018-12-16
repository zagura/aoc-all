#!/usr/bin/python3
import sys

fname = 'example.in'
if len(sys.argv) > 1:
    fname = sys.argv[1]

seq = open(fname).read()

scoreboard = [3, 7]

class Elf(object):
    def __init__(self, no):
        self.index = no
        self.id = no
    def __repr__(self):
        return str(self.__dict__)

    def move(self, scores):
        index = self.index + scores[self.index] + 1
        index %= len(scores)
        self.index = index


elf1 = Elf(0)
elf2 = Elf(1)

def recipe(e1, e2):
    result = scoreboard[e1.index] + scoreboard[e2.index]
    if result > 9:
        scoreboard.append(result // 10)
    scoreboard.append(result % 10)
    
def moves(e1, e2):
    e1.move(scoreboard)
    e2.move(scoreboard)

def print_state(e1, e2, scores):
    scores_copy = list(map(lambda x: str(x), scores))
    #scores_copy.append('')
    scores_copy = scores_copy[:e1.index] + ['(' + scores_copy[e1.index] + ')'] + scores_copy[e1.index + 1:]
    scores_copy = scores_copy[:e2.index] + ['[' + scores_copy[e2.index] + ']'] + scores_copy[e2.index + 1:]
    state = ' '.join(scores_copy)
    print(state)


#print_state(elf1, elf2, scoreboard)

if seq[-1] == '\n':
    seq = seq[:-1]
print(seq)
lst = list(map(lambda x: int(x), seq))
l = len(lst)
#print(lst)
while(True):
#for i in range(seq + 20):
    recipe(elf1, elf2)
    moves(elf1, elf2)
    if scoreboard[-l-1:-1] == lst:
        print('Found at: {}.'.format(len(scoreboard) - 1 - l))
        print(scoreboard[-l-1:-1])
        break
    elif scoreboard[-l:] == lst:
        print('Found at: {}.'.format(len(scoreboard) - l))
        break

#print_state(elf1, elf2, scoreboard)
#print(scoreboard[-l-1:-1])
#print(scoreboard[-l:])

#    print_state(elf1, elf2, scoreboard)

# result_scores = list(map(lambda x: str(x), scoreboard[total_rounds: total_rounds+10]))
# print("".join(result_scores))
