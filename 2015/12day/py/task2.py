#!/usr/bin/env python3
# task2.py
# AoC 2015 - Day 12
# --- Day 12: JSAbacusFramework.io ---

import json



def get_sum(data: dict|list) -> int:
    res = 0
    if isinstance(data, dict):
        for k, v in data.items():
            if k == "red":
                return 0
            if isinstance(v, str) and v == "red":
                return 0
        for el in data.values():
            res += get_sum(el)
    if isinstance(data, list):
        for el in data:
            res += get_sum(el)
    if isinstance(data, int):
        res = data
    return res


data = None
with open('../input.in', 'r', encoding='utf-8') as rfile:
    data = json.loads(rfile.readline())
    print(get_sum(data))

