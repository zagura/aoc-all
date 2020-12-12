#!/usr/bin/python3
from hashlib import md5

data = open('input.in').readlines()

i = 0
while True:
    temp_data = data[0] + str(i)
    hash_value = md5(temp_data.encode('utf-8')).hexdigest()
#    print(hash_value[0:6])
    if hash_value[0:6] == '000000':
        print(f"task 1 result {i}")
        break
    i += 1
