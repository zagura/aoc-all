import sys


def task1(data):
    total = 0
    for bank in data:
        m1 = max(bank[:-1])
        i1 = bank.index(m1)
        m2 = max(bank[i1+1:])
        joltage = m1 * 10 + m2
        total += joltage
    return total

def task2(data):
    return 0

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
