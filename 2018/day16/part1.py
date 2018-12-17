#!/usr/bin/python3

import sys

fname = 'input.in'
if len(sys.argv) > 1:
    fname = sys.argv[1]

lines = open(fname).readlines()

class State(object):
    def __init__(self, s):
        s = s.split('[')[1]
        s = s.split(']')[0]
        s = s.split(',')
        self.regs = list(map(lambda x: int(x), s))
    def __repr__(self):
        return str(self.__dict__)
    def deepcopy(self):
        regs = list(map(str, self.regs))
        return State('[' + ','.join(regs) + ']')

class Instruction(object):
    def __init__(self, i):
        i  = list(map(lambda x: int(x), i))
        self.opcode = i[0]
        self.A = i[1]
        self.B = i[2]
        self.C = i[3]
    def __repr__(self):
        return str(self.__dict__)

def addr(s, op):
    state = s.deepcopy()
    state.regs[op.C] = state.regs[op.A] + state.regs[op.B]
    return state

def addi(s, op):
    state = s.deepcopy()
    state.regs[op.C] = state.regs[op.A] + op.B
    return state

def mulr(s, op):
    state = s.deepcopy()
    state.regs[op.C] = state.regs[op.A] * state.regs[op.B]
    return state

def muli(s, op):
    state = s.deepcopy()
    state.regs[op.C] = state.regs[op.A] * op.B
    return state

def banr(s, op):
    state = s.deepcopy()
    state.regs[op.C] = state.regs[op.A] & state.regs[op.B]
    return state

def bani(s, op):
    state = s.deepcopy()
    state.regs[op.C] = state.regs[op.A] & op.B
    return state

def borr(s, op):
    state = s.deepcopy()
    state.regs[op.C] = state.regs[op.A] | state.regs[op.B]
    return state

def bori(s, op):
    state = s.deepcopy()
    state.regs[op.C] = state.regs[op.A] | op.B
    return state

def setr(s, op):
    state = s.deepcopy()
    state.regs[op.C] = state.regs[op.A]
    return state

def seti(s, op):
    state = s.deepcopy()
    state.regs[op.C] = op.A
    return state

def gtir(s, op):
    state = s.deepcopy()
    state.regs[op.C] = (0, 1)[op.A > state.regs[op.B]]
    return state

def gtri(s, op):
    state = s.deepcopy()
    state.regs[op.C] = (0, 1)[state.regs[op.A] > op.B]
    return state

def gtrr(s, op):
    state = s.deepcopy()
    state.regs[op.C] = (0, 1)[state.regs[op.A] > state.regs[op.B]]
    return state

def eqir(s, op):
    state = s.deepcopy()
    state.regs[op.C] = (0, 1)[op.A == state.regs[op.B]]
    return state

def eqri(s, op):
    state = s.deepcopy()
    state.regs[op.C] = (0, 1)[state.regs[op.A] == op.B]
    return state

def eqrr(s, op):
    state = s.deepcopy()
    state.regs[op.C] = (0, 1)[state.regs[op.A] == state.regs[op.B]]
    return state

operations = { 'addr': addr, 'addi': addi,
               'mulr': mulr, 'muli': muli,
               'banr': banr, 'bani': bani,
               'borr': borr, 'bori': bori,
               'setr': setr, 'seti': seti,
               'gtir': gtir, 'gtri': gtri, 'gtrr': gtrr,
               'eqir': eqir, 'eqri': eqri, 'eqrr': eqrr }

part1_result = 0
total = 0
for before, instruction, after in zip(lines[::4], lines[1::4], lines[2::4]):
    if before == '\n':
        break
    before = before[:-1].split(':')[1]
    before = State(before)
    instruction = Instruction(instruction.split())
    after = after[:-1].split(':')[1]
    after = State(after)
    matching_ops = []
    for op in operations:
        if after.regs == operations[op](before, instruction).regs:
            matching_ops.append(op)

    print("Matching_ops: {}".format(matching_ops))
    if len(matching_ops) > 2:
        part1_result += 1
    total += 1
    print("before: {}\ninstruction {}\nafter: {}".format(before, instruction, after))
print(total)
print("Part 1 result: {}".format(part1_result))
