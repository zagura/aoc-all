#!/usr/bin/python3

lines = open('input.in').readlines()

class Point(object):
    def __init__(self, x, y, _id):
        self.x = x
        self.y = y
        self.id = _id


def dist(p1, p2):
    return abs(p1.x - p2.x) + abs(p1.y - p2.y)

points = []
x_min = int(lines[0].split(',')[0])
y_min = int(lines[0].split(',')[1])
x_max, y_max = x_min, y_min

i = 0
# Save all points from file
for l in lines:
    l = l.split(',')
    if len(l) == 2:
        x = int(l[0])
        y = int(l[1])
        x_max = max(x_max, x)
        x_min = min(x_min, x)
        y_min = min(y_min, y)
        y_max = max(y_max, y)
        p = Point(x, y, i)
        points.append(p)
    i += 1
x_max += 10
y_max += 10

desired_points = 0
for x in range(x_max):
    for y in range(y_max):
        total = 0
        for p in points:
            p2 = Point(x, y , -1)
            d = dist(p, p2)
            total += d
        if total < 10000:
            desired_points += 1

print(desired_points)



