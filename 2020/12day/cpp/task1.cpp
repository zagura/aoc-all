/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2020 - Day 12
 *
 *        Version:  0.1.0
 *        Created:  12.12.2020
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
#include <queue>
#include <algorithm>

struct coords {
    int x;
    int y;
};

constexpr int dir_count = 4;
static const std::array<char, dir_count> direction_change = { 'E', 'N', 'W', 'S'};
std::unordered_map<char, coords> move_change {
    { 'E', { 1, 0 }},
    { 'N', { 0, 1 }},
    { 'W', { -1, 0}},
    { 'S', { 0, -1}}
    };
coords change_coords(coords pos, char direction, int value) {
    coords change = move_change.at(direction);
    pos.x += (change.x * value);
    pos.y += (change.y * value);
    return pos;
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
    std::vector<std::pair<char, int>> directions {};
    directions.reserve(800);
    for(std::string line; getline(input, line); ) {
        if (line.size() > 1) {
            char direction = line[0];
            int value = std::stoi(line.substr(1));
            directions.emplace_back(direction, value);
        }
    }

    // direction as index in direction_change array
    int direction = 0;
    coords position;
    position.x = 0;
    position.y = 0;
    for (auto& [dir_change, value]: directions) {
        switch (dir_change) {
        case 'N': case 'W': case 'E': case 'S':
            position = change_coords(position, dir_change, value);
            break;
        case 'L': case 'R':
            // Note: not stated in task, but changes are 90,180 or 270 degrees
            value /= 90;
            // Reverse value change if
            if (dir_change == 'R') {
                value *= -1;
            }
            direction += (dir_count + value);
            direction %= dir_count;
            break;
        case 'F':
            position = change_coords(position, direction_change[direction], value);
            break;
        }
    }

    if (position.x < 0) {
        position.x = -position.x;
    }
    if (position.y < 0) {
        position.y = -position.y;
    }

    int distance = position.x + position.y;
    ::printf("Task 1 result: %d\n", distance);
    return 0;
}

