#!/usr/bin/env python3

# AoC 2015 - Day 12
# --- Day 12: JSAbacusFramework.io ---

import json



def get_sum(data: dict|list) -> int:
    res = 0
    if isinstance(data, dict):
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

