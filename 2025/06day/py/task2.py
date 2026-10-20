#!/usr/bin/python3

import sys

fname = "../input.in"
if len(sys.argv) > 1:
    fname = sys.argv[1]

def task2(fname):
    args = []
    rows = []
    with open(fname, 'r', encoding='utf-8') as f:
        data = f.readlines()
        for row in data[:-1]:
            rows.append(row.strip().split())

    for i in range(len(rows[0])):
        col = [row[i] for row in rows]
        lens = max([len(x) for x in col])
        numbers = []
        for d in list(range(lens))[::-1]:
            n = 0
            for c in col:
                if len(c) > d:
                    print(f"Add {c[d]} to existing {n}")
                    n = n * 10 + int(c[d])
            numbers.append(n)
        print(f"Column {i}: {numbers}")
        args.append(list(numbers))


    symbols = data[-1].strip().split()
    total = get_total(args, symbols)
    print(f"Total: {total}")

def task2_2(fname):
    with open(fname, 'r', encoding='utf-8') as f:
        data = f.readlines()
        for d in data:
            # Skip \n at the end
            d = d[:-1]
    lens = max([len(x) for x in data])
    symbols = data[-1]
    data = data[:-1]
    args = []
    numbers = []
    for i in range(lens):
        n = ""
        for row in data:
            n += row[i]
        if n.strip() == "":
            args.append(list(numbers))
            numbers = []
        else:
            numbers.append(int(n))
    total = get_total(args, symbols.split())
    print(f"Task 2 total: {total}")

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

task2_2(fname)
