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
i = 0
x_min = int(lines[0].split(',')[0])
y_min = int(lines[0].split(',')[1])
x_max, y_max = x_min, y_min
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
print('{} {} : {} {}'.format(x_min, x_max, y_min, y_max))
x_max += 10
y_max += 10
puzzle = [[[] for y in range(y_max)] for x in range(x_max)]
point_count = {}
excluded = []
eq = 0
for p in points:
    print(p.__dict__)
    point_count[p.id] = 0
for x in range(x_max):
    for y in range(y_max):
        ds = []
        for p in points:
            p2 = Point(x, y , -1)
            d = dist(p, p2)
            entry = (p.id, d)
            ds.append(entry)
        ds.sort(key=lambda x: x[1])
#        print("{} {}".format(ds[0], ds[1]))
        puzzle[x][y] = ds
        if ds[0][1] != ds[1][1]:
            point_count[ds[0][0]] += 1
            if x == 0 or x == x_max - 1 or y == 0 or y == y_max - 1:
                excluded.append(ds[0][0])
        else:
            eq += 1

print(eq)
l2 = point_count.items()
l2.sort(key=lambda x: x[1])
print(l2)
print(' ')
point_count = list(filter(lambda (k, v): k not in excluded, point_count.items()))

point_count.sort(key=lambda x: x[1])
print(point_count)



