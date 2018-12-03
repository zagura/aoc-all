#!/usr/bin/python

lines = open('input.in').readlines()

inches = 1000
puzzle = [[-1 for i in range(inches)] for j in range(inches)]
claims = []
class Claim(object):
    def __init__(self, row):
        self.id = self.get_id(row)
        self.x, self.y = self.get_dims(row)
        self.width, self.height = self.get_size(row)
        self.free = True

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
        claims.append(claim)
        for i in range(claim.width):
            for j in range(claim.height):
                x = claim.x + i
                y = claim.y + j
                if puzzle[x][y] == -1:
                    puzzle[x][y] = claim.id
                else:
                    claims[-1].free = False
                    claims[puzzle[x][y] - 1].free = False

    for claim in claims:
        if claim.free == True:
            print("Claim id: {}".format(claim.id))

__main__()

