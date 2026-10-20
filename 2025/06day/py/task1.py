#!/usr/bin/python3

import sys

fname = "../input.in"
if len(sys.argv) > 1:
    fname = sys.argv[1]

def task1(fname):
    args = []
    rows = []
    with open(fname, 'r', encoding='utf-8') as f:
        data = f.readlines()
        for row in data[:-1]:
            rows.append([int(n) for n in row.strip().split()])

    for i in range(len(rows[0])):
        args.append([row[i] for row in rows])

    symbols = data[-1].strip().split()
    total = get_total(args, symbols)
    print(f"Total: {total}")

def get_total(args, symbols):
    total = 0
    for i in range(len(symbols)):
        partial = 0
        if symbols[i] == '+':
            partial = sum(args[i])
        elif symbols[i] == '*':
            partial = 1
            for a in args[i]:
                partial *= a
        total += partial
    return total

task1(fname)
