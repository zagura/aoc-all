/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2022 - Day 9
 *
 *        Version:  0.1.0
 *        Created:  09.12.2022
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <array>
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
#include <queue>

static std::array<int, 4> delta_x = { -1, 1, 0, 0 };
static std::array<int, 4> delta_y = { 0, 0, -1, 1 };

// first - horizontal move (left, right)
// second - vertical move (up, down)

const std::map<char, std::pair<int, int>> moves {
    { 'R', {  1,  0 }},
    { 'U', {  0,  1 }},
    { 'L', { -1,  0 }},
    { 'D', {  0, -1 }}
};

void make_move(std::pair<int, int>& head,
               std::pair<int, int>& tail,
               std::set<std::pair<int, int>>& trail,
               char direction) {

    std::pair<int, int> diff = moves.at(direction);
    head.first += diff.first;
    head.second += diff.second;
    bool vertical = false, horizontal = false;
    if (head.first - tail.first > 1) {
        tail.first++;
        horizontal = true;
    } else if (head.first - tail.first < -1) {
        tail.first--;
        horizontal = true;
    }
    if (head.second - tail.second > 1) {
        vertical = true;
        tail.second++;
    } else if (head.second - tail.second < -1) {
        vertical = true;
        tail.second--;
    }
    if (!horizontal && vertical && head.first != tail.first) {
        tail.first += (head.first > tail.first) ? 1 : -1;
    } else if (!vertical && horizontal && head.second != tail.second) {
        tail.second += (head.second > tail.second) ? 1 : -1;
    }
    trail.insert(tail);
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
    std::pair<int, int> head (0, 0);
    std::pair<int, int> tail (0, 0);
    std::set<std::pair<int, int>> trail;
    for (std::string line; getline(input, line); ) {
        std::stringstream line_stream { line };
        char direction;
        int step_count;
        line_stream >> direction >> step_count;
        for (int i = 0; i < step_count; i++) {
            make_move(head, tail, trail, direction);
        }
    }

    ::printf("Task 1 result: %zu\n", trail.size());
    return 0;
}

