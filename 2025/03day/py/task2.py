import sys

def joltage(bank, count, base):
    if count < 0:
        return base
    if count > 0:
        m1 = max(bank[:-count])
    else:
        m1 = max(bank)
    base = base * 10 + m1
    return joltage(bank[bank.index(m1) + 1:], count - 1, base)



def task1(data):
    total = 0
    for bank in data:
        j = joltage(bank, 1, 0)
        m1 = max(bank[:-1])
        i1 = bank.index(m1)
        m2 = max(bank[i1+1:])
        old_j = m1 * 10 + m2
        total += old_j
        if old_j != j:
            print(f"Something wrong: {j=} != {old_j=}")
    return total

def task2(data):
    total = 0
    for bank in data:
        j = joltage(bank, 11, 0)
        print(f"joultage: {j=}")
        total += j
    return total


def main():
    input_file = '../input.in'
    if len(sys.argv) > 1:
        input_file = sys.argv[1]

    with open(input_file, 'r', encoding='utf-8') as f:
        banks = []
        for line in f.readlines():
            sline = line.strip()
            if len(sline) == 0:
                continue
            bank = [int(i) for i in sline]
            banks.append(bank)
    res1 = task1(banks)
    res2 = task2(banks)
    print(f"Task 1 result: {res1}")
    print(f"Task 2 result: {res2}")




main()
