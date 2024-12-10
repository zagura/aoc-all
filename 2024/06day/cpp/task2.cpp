/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2024 - Day 6
 *
 *        Version:  0.2.0
 *        Created:  10.12.2024
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <string>
#include <fstream>
#include <format>
#include <cinttypes>
#include <vector>
#include <print>
#include <map>
#include <set>

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

class Task {
public:
    Task() : lab(), start_pos() {}
    std::vector<std::string> lab;
    std::set<std::pair<int, int>> possible_obstructions {};
    std::pair<int, int> start_pos;
    bool step(std::pair<int, int>& current_pos, direction& current_dir);
    bool step2(std::pair<int, int>& current_pos, direction& current_dir);
    bool bounded(const std::pair<int, int>& coords) const;
    bool find_loop(const std::pair<int, int> s, direction d);
    void print() {
        for (const auto& s: lab) {
            std::println("{}", s);
        }
        std::println("");
    }
};

std::pair<int, int> next(const std::pair<int, int>& prev, direction d) {
    switch (d) {
        case direction::up: return { prev.first - 1, prev.second };
        case direction::right: return { prev.first, prev.second + 1 };
        case direction::down: return { prev.first + 1, prev.second };
        case direction::left: return { prev.first, prev.second - 1 };
    }
    return prev;
}

std::pair<int, int> prev(const std::pair<int, int>& old, direction d) {
    d  = next_dir(next_dir(d));
    return next(old, d);
}

bool Task::bounded(const std::pair<int, int>& coords) const {
    return coords.first >= 0 && coords.first < static_cast<int>(lab.size())
           && coords.second >= 0  && coords.second < static_cast<int>(lab.begin()->size());
}

bool Task::step(std::pair<int, int>& current_pos, direction& current_dir) {
    if (not bounded(current_pos)) {
        return false;
    }
    auto next_pos = next(current_pos, current_dir);
    if (not bounded(next_pos)) {
        return false;
    }
    auto [x, y] = next_pos;
    if (lab[x][y] != '#' && lab[x][y] != 'O') {
        lab[x][y] = 'X';
        current_pos = next_pos;
    } else {
        current_dir = next_dir(current_dir);
    }
    return true;
}

bool Task::find_loop(std::pair<int, int> s, direction d) {
    auto probe1 = s;
    auto dir1 = d;
    auto probe2 = s;
    auto dir2 = d;
    int steps = 0;
    while (step(probe1, dir1) && step(probe1, dir1)) {
        step(probe2, dir2);
        steps++;
        if (probe1 == probe2 && dir1 == dir2) {
            print();
            std::println("Loop size: {}", steps);
            return true;
        }
    }
    return false;
}

bool Task::step2(std::pair<int, int>& current_pos, direction& current_dir) {
    if (not bounded(current_pos)) {
        return false;
    }
    auto next_pos = next(current_pos, current_dir);
    if (not bounded(next_pos)) {
        return false;
    }
    auto [x, y] = next_pos;
    if (lab[x][y] != '#' && lab[x][y] != 'O') {
        if (lab[x][y] != 'X') {
            Task t2 = *this;
            t2.lab[x][y] = 'O';
            if (t2.find_loop(current_pos, current_dir)) {
                possible_obstructions.emplace(x, y);
            }
        }
        lab[x][y] = 'X';
        current_pos = next_pos;
    } else {
        current_dir = next_dir(current_dir);
        // return step(current_pos, current_dir);
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
    Task t {};
    t.lab = lab;
    t.start_pos = pos;
    // // Count X
    uint64_t total = 0;
    t.step(pos, current);
    while(t.step2(pos, current));
    for (const auto& s: t.lab) {
        for(const auto& c: s) {
            total += (c == 'X') ? 1 : 0;
        }
    }
    t.possible_obstructions.erase(pos);
    std::println("Task 1 result: {}", total);
    std::println("Task 2 result: {}", t.possible_obstructions.size());
    return 0;
}

