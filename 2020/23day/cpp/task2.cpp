/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2020 - Day 23
 *
 *        Version:  0.2.0
 *        Created:  02.01.2021
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <array>
#include <map>
#include <list>
#include <vector>
#include <cinttypes>

constexpr int million = 1000 * 1000;
constexpr size_t kCupsSize = million;
constexpr int kRoundCount = 10 * million;
constexpr size_t kPickupSize = 3;

using std::string;
using std::vector;
using std::array;
using std::map;
using std::stringstream;
using Cups = std::vector<int>;


void next_move(Cups& cups, int& current) {
    std::array<int, kPickupSize> pick_up;
    pick_up[0] = cups[current];
    for (size_t i = 1; i < kPickupSize; i++) {
        pick_up[i] = cups[pick_up[i-1]];
    }
    // Skip pick_up part
    int destination = current - 1;
    current = cups[current] = cups[pick_up.back()];


    if (destination == 0) {
        destination = kCupsSize;
    }
    while (std::find(pick_up.begin(), pick_up.end(), destination) != pick_up.end()) {
        destination--;
        if (destination < 1) {
            destination = kCupsSize;
        }
    }
    cups[pick_up.back()] = cups[destination];
    cups[destination] = pick_up.front();
}

int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    if (!input.good()) {
        ::fprintf(stderr, "Cannot open input file\n");
        return 2;
    }

    string line;
    getline(input, line);
    Cups cups {};
    cups.resize(kCupsSize + 1);
    int last = kCupsSize;
    int start = line.front() - '0';

    for (char c: line) {
        int val = c - '0';
        cups[last] = val;
        last = val;
    }

    for (size_t s = line.size() + 1; s <= kCupsSize; ++s) {
        cups[last] = s;
        last = s;
    }

    for (size_t round = 0; round < kRoundCount; round++) {
        next_move(cups, start);
    }

    uint64_t a = cups[1];
    uint64_t b = cups[a];
    printf("\n");
    printf("Part 2 result: %" PRIu64 "\n", a * b);
    return 0;
}

