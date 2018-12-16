#!/usr/bin/python3

import sys
import queue
from typing import Dict, Any, Union


verbosity = 0
fname = 'example.in'
elf_attack = 3
if len(sys.argv) > 1:
    fname = sys.argv[1]
if len(sys.argv) > 2:
    elf_attack = sys.argv[2]

lines = open(fname).readlines()

wall = '#'
empty = '.'
global_width = len(lines[0])
enemy_str = { 'E' : 'G', 'G': 'E' }
space = [ list(x[:-1]) for x in lines ]

goblins = []
elves = []
def l2s(l):
    return [ str(i) for i in l ]
def print_space(space_map):
    for l in space_map:
        print(''.join(l2s(l)))

class MapPoint(object):
    def __init__(self, x, y, no):
        self.x = x
        self.y = y
        self.target_id = no
        self.dist = 9000


def create_move_targets(target_list):
    targets = []
    for t in target_list:
        for x, y in zip([-1, 0, 0, 1], [0, -1, 1, 0]):
            if str(space[t.x + x][t.y + y]) == '.':
                p = MapPoint(t.x + x, t.y + y, t.id)
                targets.append(p)
    return targets

def dist_key(p):
    return p.dist

def get_neighbors(x, y):
    neighbors = []
    for (diff_x, diff_y) in zip([0, -1, 1, 0], [-1, 0, 0, 1]):
            if str(space[x+diff_x][y+diff_y]) == '.':
                p = MapPoint(x + diff_x, y+diff_y, -1)
                neighbors.append(p)
    return list(set(neighbors))

def get_bfs(x, y):
    q = queue.Queue()
    result = {}
    result[x] = {y : 0}
    p = MapPoint(x, y, -1)
    p.dist = 0
    q.put(p)
    while(not q.empty()):
        current_node = q.get()
        for n in get_neighbors(current_node.x, current_node.y):
            if n.x not in result:
                result[n.x] = {}
            if n.y not in result[n.x]:
                n.dist = current_node.dist + 1
                result[n.x][n.y] = n.dist
                q.put(n)
    return result

def get_nerest(x, y, name):
    neighbors = []
    for (diff_x, diff_y) in zip([0, -1, 1, 0], [-1, 0, 0, 1]):
            if str(space[x+diff_x][y+diff_y]) == name:
                neighbors.append(space[x+diff_x][y+diff_y])
    return neighbors


def reading_key(m):
    return m.x * global_width + m.y

class Member(object):
    def __init__(self,  no, x, y):
        self.name = 'N'
        self.id = no
        self.hp = 200
        self.attack_power = 3
        self.x = x
        self.y = y

    def move(self, enemies):
        n1 = get_nerest(self.x, self.y, enemy_str[self.name])
        if len(n1) > 0:
            return self.attack(n1, enemies)
        targets1 = create_move_targets(enemies)
        if targets1 == []:
            return enemies
        graph = get_bfs(self.x, self.y)
        for t in targets1:
            if t.x in graph:
                if t.y in graph[t.x]:
                    t.dist = graph[t.x][t.y]
        targets1.sort(key=dist_key)
        targets2 = list(filter(lambda x: x.dist == targets1[0].dist, targets1))
        targets2.sort(key=reading_key)
        target = targets2[0]
        self.change_position(target)
        n2 = get_nerest(self.x, self.y, enemy_str[self.name])
        if len(n2) > 0:
            return self.attack(n2, enemies)
        return enemies

    def change_position(self, target):
        graph = get_bfs(target.x, target.y)
        neighbors = get_neighbors(self.x, self.y)
        Mappoints = []
        for n in neighbors:
            if n.x in graph:
                if n.y in graph[n.x]:
                    d = graph[n.x][n.y]
                    p = MapPoint(n.x, n.y, self.id)
                    p.dist = d
                    Mappoints.append(p)
        Mappoints.sort(key=dist_key)
        if len(Mappoints) == 0:
            return
        min_dist = Mappoints[0].dist
        Mappoints = list(filter(lambda x: x.dist == min_dist, Mappoints))
        Mappoints.sort(key=reading_key)
        place = Mappoints[0]
        space[place.x][place.y] = self
        space[self.x][self.y] = '.'
        self.x = place.x
        self.y = place.y


    def attack(self, candidates, enemies_list):
        candidates.sort(key=lambda g: g.hp)
        min_hp = candidates[0].hp
        candidates = list(filter(lambda g: g.hp == min_hp, candidates))
        candidates.sort(key=reading_key)
        target = candidates[0]
        target.hp = target.hp - self.attack_power
        if self.hp < 0:
            return enemies_list
        if target.hp < 0:
            space[target.x][target.y] = '.'
            enemies_list = list(filter(lambda en: en.id != target.id, enemies_list))
        return enemies_list

    # def dist(self, other):
    #     return abs(self.x - other.x) + abs(self.y - other.y)
    
    def __repr__(self):
        return self.name

class Goblin(Member):
    def __init__(self, no, x, y):
        super().__init__(no, x, y)
        self.name = 'G'
    

class Elf(Member):
    def __init__(self, no, x, y):
        super().__init__(no, x, y)
        self.name = 'E'
        self.attack_power = int(elf_attack)



ids = 0
for x in range(len(space)):
    for y in range(len(space[x])):
        if space[x][y] == 'G':
            g = Goblin(ids, x, y)
            goblins.append(g)
            space[x][y] = g
            ids += 1
        elif space[x][y] == 'E':
            e = Elf(ids, x, y)
            elves.append(e)
            space[x][y] = e
            ids += 1


for g in goblins:
    print("goblin: ({}, {}).".format(g.x, g.y))
print("Elves count before: {}".format(len(elves)))
before = len(elves)
for e in elves:
    print("elf: ({}, {}).".format(e.x, e.y))


def play_game(goblins, elves):
    round_number = 0
    while(len(goblins) > 0 and len(elves) > 0):
        # print("\n\nRound: {}".format(round_number))
        team = goblins + elves
        team.sort(key=reading_key)
        for t in team:
            if t.name == 'E' and t in set(elves):
                goblins = t.move(goblins)
            elif t.name == 'G' and t in set(goblins):
                elves = t.move(elves)
            if len(goblins) == 0 or len(elves) == 0 and t != team[-1]:
                print('Middle of round: {}'.format(round_number))
                return (goblins, elves, round_number)
        round_number += 1
        if verbosity > 0:
            for g in goblins:
                 print("goblin: ({}, {}) {}.".format(g.x, g.y, g.hp))
            for e in elves:
                print("elf: ({}, {}) {}.".format(e.x, e.y, e.hp))
            print_space(space)
    return (goblins, elves, round_number)

(goblins, elves, rNo) = play_game(goblins, elves)
print("Total rounds: {}".format(rNo))
total_hp = 0
for g in goblins:
    total_hp += g.hp
for e in elves:
    total_hp += e.hp
print("Total HP: {}".format(total_hp))
result = total_hp * rNo
print("Result: {}".format(result))
## Part 2
print("Elves count after: {}".format(len(elves)))
if len(elves) == before:
    print("+++++++++++++++++ SUCCESS +++++++++++++")
## End of part 2
# print_space(space)
chars = goblins + elves
chars.sort(key=reading_key)
for c in chars:
    print("{}: ({}, {}) ({})".format(c.name, c.x, c.y, c.hp))
print_space(space)

