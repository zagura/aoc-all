#!/usr/bin/python

lines = open('input1.in').readlines()

lines = list(map(lambda x: x[:-1], lines))


def word_diff(w1, w2):
    diff_count = 0
    for c1,c2 in zip(w1, w2):
        if c1 != c2:
            diff_count += 1
    return diff_count


def get_word(w1, w2):
    word = ""
    for c1, c2 in zip(w1, w2):
        if c1 == c2:
            word = word + c1
    return word

for i in range(len(lines) - 1):
    for j in range(i, len(lines)):
        if word_diff(lines[i], lines[j]) == 1:
            print("Diff between {} and {} is 1.".format(lines[i], lines[j]))
            print("Resulted common substring is {}.".format(get_word(lines[i], lines[j])))


print('')


