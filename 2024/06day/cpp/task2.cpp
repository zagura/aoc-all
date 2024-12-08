/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2024 - Day 6
 *
 *        Version:  0.1.0
 *        Created:  07.12.2024
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */

#include <iostream>
#include <string>
#include <fstream>
#include <format>
#include <cinttypes>
#include <vector>
#include <sstream>

enum class direction {
    up = 1,
    right = 2,
    down = 3,
    left = 4
};

direction next_dir(direction d) {
    switch(d) {
    case direction::up:
        return direction::right;
    case direction::right:
        return direction::down;
    case direction::down:
        return direction::left;
    case direction::left:
        return direction::up;
    }
    return d;
}



std::pair<int, int> next(const std::pair<int, int>& prev, direction d) {
    switch (d) {
        case direction::up: return { prev.first - 1, prev.second };
        case direction::right: return { prev.first, prev.second + 1 };
        case direction::down: return { prev.first + 1, prev.second };
        case direction::left: return { prev.first, prev.second - 1 };
    }
    return prev;
}

bool bounded(const std::vector<std::string>& data, const std::pair<int, int>& coords) {
    return coords.first >= 0 && coords.first < static_cast<int>(data.size())
           && coords.second >= 0  && coords.second < static_cast<int>(data.begin()->size());
}

bool step(std::vector<std::string>& lab, std::pair<int, int>& current_pos, direction& current_dir) {
    if (not bounded(lab, current_pos)) {
        return false;
    }
    auto next_pos = next(current_pos, current_dir);
    if (not bounded(lab, next_pos)) {
        return false;
    }
    auto [x, y] = next_pos;
    if (lab[x][y] != '#') {
        lab[x][y] = 'X';
        current_pos = next_pos;
        return true;
    } else {
        current_dir = next_dir(current_dir);
        return true;
    }
    return true;
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
    std::vector<std::string> lab {};
    std::vector<std::pair<int, int>> walls {};
    std::pair<int, int> pos {};
    direction current = direction::up;
    for(std::string line; getline(input, line);) {
        if (line.size() == 0 || line == "\n") {
            continue;
        }
        for (size_t i = 0; i < line.size(); i++) {
            if (line[i] == '#') {
                walls.emplace_back(lab.size(), i);
            } else if (line[i] == '^') {
                pos = { lab.size(), i };
            }
        }
        lab.push_back(line);
    }

    lab[pos.first][pos.second] = 'X';
    while(step(lab, pos,current));
    // Count X
    uint64_t total = 0;
    for (const auto& s: lab) {
        for(const auto& c: s) {
            total += (c == 'X') ? 1 : 0;
        }
    }

    ::printf("Task 1 result: %" PRIu64 "\n", total);
    return 0;
}

