#!/usr/bin/python3

# p_input = 3031
import sys
p_input = sys.argv[1]

def calculate(x, y):
    rack_id = x + 10
    print("Rack ID: {}".format(rack_id))
    power_level = rack_id * y
    print("Power level starts {}".format(power_level))
    power_level += p_input
    print(power_level)
    power_level *=  rack_id
    power_level = power_level // 100
    print(power_level)
    power_level %= 10
    print(power_level)
    power_level -= 5
    print(power_level)
    return power_level

