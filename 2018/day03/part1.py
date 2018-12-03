#!/usr/bin/python

lines = open('input.in').readlines()

inches = 1000
puzzle = [[0 for i in range(inches)] for j in range(inches)]

class Claim(object):
    def __init__(self, row):
        self.id = self.get_id(row)
        self.x, self.y = self.get_dims(row)
        self.width, self.height = self.get_size(row)

    def get_id(self, row):
        return int(row.split('@')[0][1:])

    def get_dims(self, row):
        row = row.split('@')[1]
        row = row.split(':')[0]
        row = row.split(',')
        x = int(row[0])
        y = int(row[1])
        return (x, y)

    def get_size(self, row):
        row = row.split(':')[1]
        row = row.split('x')
        w = int(row[0])
        h = int(row[1])
        return (w, h)

    def __repr__(self):
        return str(self.__dict__)


def __main__():
    for line in lines:
        claim = Claim(line)
        for i in range(claim.width):
            for j in range(claim.height):
                puzzle[claim.x+i][claim.y+j] += 1

    count = 0
    for i in puzzle:
        for j in i:
            if j > 1:
                count += 1

    print("Total count: {}".format(count))

__main__()

