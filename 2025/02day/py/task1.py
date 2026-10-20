import sys


def task1(data):
    ranges = data.split(',')
    count = 0
    invalid = []
    for r in ranges:
        nums = r.split('-')
        begin = int(nums[0])
        end = int(nums[1])
        for n in range(begin, end + 1):
            s = str(n)
            l = len(s)
            if l % 2 == 0 and s[:l // 2] == s[l // 2:]:
                invalid.append(n)
                print(f"range: {r}, num: {n}")
    return sum(invalid)


def task2(data):
    ranges = data.split(',')
    count = 0
    invalid = []
    for r in ranges:
        nums = r.split('-')
        begin = int(nums[0])
        end = int(nums[1])
        for n in range(begin, end + 1):
            s = str(n)
            l = len(s)
            for i in range(2, l + 1):
                if l % i == 0:
                    d = l // i
                    sl = set()
                    t = range(0, l)
                    for s1 in t[::d]:
                        sl.add(s[s1: s1 + d])
                    if len(sl) == 1:
                        invalid.append(n)
                        print(f"range: {r}, num: {n}, repeat: {i}")
                        break
    return sum(invalid)


def main():
    input_file = '../input.in'
    if len(sys.argv) > 1:
        input_file = sys.argv[1]

    with open(input_file, 'r', encoding='utf-8') as f:
        for line in f.readlines():
            sline = line.strip()
            if len(sline) == 0:
                continue
            res1 = task1(sline)
            res2 = task2(sline)

    print(f"Task 1 result: {res1}")
    print(f"Task 2 result: {res2}")




main()
