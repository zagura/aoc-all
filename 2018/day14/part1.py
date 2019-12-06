#!/usr/bin/python3
import sys

fname = 'example.in'
if len(sys.argv) > 1:
    fname = sys.argv[1]

total_rounds = int(open(fname).read())

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
    
print(total_rounds)
for r in range(total_rounds + 10):
    recipe(elf1, elf2)
    moves(elf1, elf2)
    if len(scoreboard) > total_rounds + 10:
        break
#    print_state(elf1, elf2, scoreboard)

result_scores = list(map(lambda x: str(x), scoreboard[total_rounds: total_rounds+10]))
print("".join(result_scores))
