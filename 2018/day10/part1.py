#!/usr/bin/python3

import sys
input_file = 'in0.in'
if len(sys.argv) > 1:
    input_file = sys.argv[1]

lines = open(input_file).readlines()

class Point(object):
    def __init__(self, row):
        row = row.split('<')
        position = row[1].split('>')[0]
        position = position.split(',')
        self.x = int(position[0])
        self.y = int(position[1])
        vel = row[2].split('>')[0]
        vel = vel.split(',')
        self.vel_x = int(vel[0])
        self.vel_y = int(vel[1])
    
    def pass_second(self):
        self.x = self.x + self.vel_x
        self.y = self.y + self.vel_y
        return self
    
    def undo_second(self):
        self.x = self.x - self.vel_x
        self.y -= self.vel_y
        return self

    def __repr__(self):
        return str(self.__dict__)

def get_width(points):
    #    print(len(points))
    min_x = min(list(map(lambda x: x.x, points)))
    max_x = max(list(map(lambda x: x.x, points)))
    return max_x - min_x
def get_height(points):
    min_y = min(list(map(lambda x: x.y, points)))
    max_y = max(list(map(lambda x: x.y, points)))
    return max_y - min_y

def draw_image(points):
    min_x = min(list(map(lambda x: x.x, points)))
    min_y = min(list(map(lambda x: x.y, points)))
    max_y = max(list(map(lambda x: x.y, points)))
    max_x = max(list(map(lambda x: x.x, points)))
    drawing = [['.' for i in range(min_x - 2, max_x + 2)] for j in range(min_y - 2, max_y + 2)]
    for p in points:
        x = p.x - min_x + 2
        y = p.y - min_y + 2
        drawing[y][x] = '#'
    for r in drawing:
        print(''.join(r))

points = []
print(len(lines))
for l in lines:
    points.append(Point(l))


min_width = get_width(points)
min_height = get_height(points)
current_time = 0
def next_second(points):
    return list(map(lambda x: x.pass_second(), points))

def prev_sec(p):
    return list(map(lambda x: x.undo_second(), p))

while(True):
    points = next_second(points=points)
    current_time += 1
    current_height = get_height(points)
    if min_height > current_height:
        min_height = current_height
    else:
        points = prev_sec(points)
        print(current_time - 1)
        draw_image(points)
        break



