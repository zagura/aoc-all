#!/usr/bin/python3
from datetime import date, time

# first sort in bash
lines = open('input.in').readlines()

def get_state(msg):
    print(msg)
    if msg[:-1] == 'falls asleep':
        return 1
    elif msg[:-1] == 'wakes up':
        return 0

def get_minute(timestamp):
    minute = timestamp.split(':')[1]
    print('{} {}.'.format(minute, int(minute)))
    return int(minute)


guards = {}

class Guard(object):
    def __init__(self, num):
        self.id = num
        self.times = []
        self.total = 0
        self.freq = [0 for x in range(60)]

    def add(self, minutes):
        # print(minutes)
        self.times.append(minutes)

    def get_total(self):
        total = 0
        for t in self.times:
            if len(t) != 60:
                pass
            for i in range(60):
                total += t[i]
                self.freq[i] += t[i]
        self.total = total

    def get_most_frequent(self):
        index = 0
        maxed = 0
        for i in range(60):
            if self.freq[i] > maxed:
                maxed = self.freq[i]
                index = i
        return index

        

_id = -1
guard = None
minutes = [0 for x in range(60)]
begin = 0
sleeped = 0
for row in lines:
    if len(row) == 0:
        pass
    timestamp = row.split(']')[0][1:]
    msg = row.split(']')[1][1:]
    if len(msg.split('#')) == 2:
        if _id != -1:
            for m in range(begin, 60):
                minutes[m] = sleeped
            if _id in guards:
                # print(minutes)
                guards[_id].add(minutes)
            else:
                guard = Guard(_id)
                guards[_id] = guard
                guards[_id].add(minutes)
        _id = msg.split('#')[1].split(' ')[0]
        _id = int(_id)
        minutes = [0 for x in range(60)]
        begin = 0
        sleeped = 0
    else:
        print(sleeped)
        minute = get_minute(timestamp)
        print(minute)
        for m in range(begin, minute):
            minutes[m] = sleeped
        begin = minute
        sleeped = get_state(msg)

guard_list = []
for g in guards.values():
    g.get_total()
    guard_list.append(g)

sorted_guards = sorted(guard_list, key=lambda x: x.total, reverse=True)

print(sorted_guards[0].__dict__)
for g in sorted_guards:
    print('Id: {} : total {}'.format(g.id, g.total))
guard_id = sorted_guards[0].id
guard_freq_minute = sorted_guards[0].get_most_frequent()
print("Total: {}*{} = {}.".format(guard_id, guard_freq_minute, guard_id*guard_freq_minute))



