#!/usr/bin/python3
import sys

fname = 'example2.in'
if len(sys.argv) > 1:
	fname = sys.argv[1]

lines = open(fname).readlines()

def remove_newline(line):
	if line[-1] == '\n':
		line = str(line[:-1])
	return line

lines = list(map(remove_newline, lines))

left = 'left'
right = 'right'
north = 'north'
south = 'south'
east = 'east'
west = 'west'
forward = 'forward'
class Cart(object):
	tournaments = { left: forward, forward: right, right: left}
	directions = { left :   {north: west, west: south, south: east, east: north},
				   right:   {north: east, west: north, south: west, east: south},
				   forward: {north: north, west: west, south: south, east: east}}
	turns = { '/': { west: south, east: north, south: west, north: east },
			  '\\': { west: north, east: south, south: east, north: west }}

	Xs = { north: 0, south: 0 , west: -1, east: 1 }
	Ys = { north: -1, south: 1, west: 0, east: 0 }

	def __init__(self, no, x, y, direction):
		self.id = no
		self.x = x
		self.y = y
		self.direction = direction
		self.tournament = left

	def next_tournament(self):
		self.tournament = Cart.tournaments[self.tournament]

	def next_direction(self):
		self.direction = Cart.directions[self.tournament][self.direction]

	def set_turn(self, c):
	   	self.direction = Cart.turns[c][self.direction]

	def intersect(self):
		self.next_direction()
		self.next_tournament()

	def change_position(self):
		self.x = self.x + Cart.Xs[self.direction]
		self.y = self.y + Cart.Ys[self.direction]

	def check_collisions(self, other):
		for o in other:
			if o.x == self.x and o.y == self.y and self.id != o.id:
				return o
		return None

	def movement(self, full_map):
		self.change_position()
		sign = full_map[self.y][self.x]
		if sign == '+':
			self.intersect()
		elif sign == '/' or sign == '\\':
			self.set_turn(sign)
	def __repr__(self):
		return str(self.__dict__)

def print_map(map_list):
	for row in map_list:
		print(row)
	
initial_directions = {'<': west , '>': east, '^': north, 'v': south }
marks = {south: 'v', north: '^', east: '>', west: '<'}
direction_lines = { north: '|', south: '|', east: '-', west: '-'}
carts = []
cart_count = 1
print_map(lines)
tracks = lines[:]
for i in range(len(lines)):
	for j in range(len(lines[i])):
		if lines[i][j] in initial_directions:
			c = Cart(cart_count, j, i, initial_directions[lines[i][j]])
			carts.append(c)
			cart_count += 1
			l = list(lines[i])
			l[j] = direction_lines[c.direction]
			tracks[i] = "".join(l)
print_map(tracks)

def tick(cart_list, track_map):
	#cart_list = sorted(cart_list, lambda x: x.y)
	rows = {}
	for y in range(len(lines)):
		cart_row = sorted(filter(lambda el: el.y == y, cart_list), key=lambda v: v.x)
		# cart_row.sort(key=lambda val: val.x)
		rows[y] = cart_row
	#print(rows)
	for r in rows:
		for cart in rows[r]:
			old_row = cart.y
			old_x = cart.x
			cart.movement(full_map=track_map)
			collision = False
			collider = None
			for col in range(old_row - 2, old_row + 3):
				if col in rows:
					c = cart.check_collisions(rows[col])
					if c is not None:
						collider = c
			if collider:
				print("Collision at: ({},{})".format(cart.x, cart.y))
				cart_list = list(filter(lambda x: x.id != cart.id and x.id != collider.id, cart_list))
	return cart_list

def mark_map(track_map, carts):
	marked_map = [list(e) for e in track_map]
	for c in carts:
		marked_map[c.y][c.x] = marks[c.direction]
	marked_map = ["".join(e) for e in marked_map]
	return marked_map

epoch = 0
print(carts)
print_map(lines)
print_map(tracks)
while(len(carts) > 1):
	carts = tick(carts, tracks)
	# print_map(lines)
	#print(carts)
	#print_map(mark_map(tracks, carts))
	epoch += 1

print(carts)

print("Epoch: {}".format(epoch))



