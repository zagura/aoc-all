# Part 1
def fuel_formula(mass):
    m = int(mass // 3)
    return m - 2

def main():
    lines = open('input1.in').readlines()
    total_fuel = 0
    if lines[-1] == '\n':
        lines = lines[:-1]
    for l in lines:
        total_fuel += fuel_formula(int(l.strip()))
    print(total_fuel)
if __name__ == "__main__":
    main()
