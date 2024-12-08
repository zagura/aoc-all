/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2024 - Day 8
 *                  --- Day 8: Resonant Collinearity ---
 *
 *        Version:  0.1.0
 *        Created:  08.12.2024
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <algorithm>
#include <cinttypes>
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
#include <format>
#include <print>
#include <vector>

using Point = std::pair<int, int>;

class Task {
public:

    bool bounded(const std::pair<int, int>& coords) const;
    std::vector<std::string> data {};
    std::map<char, std::vector<std::pair<int, int>>> antennas {};
    std::pair<Point, Point> counter_antennas(const Point& a, const Point& b);
};

bool Task::bounded(const std::pair<int, int>& coords) const {
    return coords.first >= 0 && coords.first < static_cast<int>(data.size())
        && coords.second >= 0  && coords.second < static_cast<int>(data.begin()->size());
}

std::pair<Point, Point> Task::counter_antennas(const Point& a, const Point& b) {
    int d_x = b.first - a.first;
    int d_y = b.second - a.second;
    return {
        { b.first + d_x, b.second + d_y },
        { a.first - d_x, a.second - d_y }
    };
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

    Task t {};
    for(std::string line; getline(input, line);) {
        if (line.size() == 0 || line == "\n") {
            continue;
        }
        for (size_t i = 0; i < line.size(); i++) {
            if (line[i] != '.') {
                t.antennas[line[i]].emplace_back(t.data.size(), i);
            }
        }
        t.data.push_back(line);
    }

    size_t count = 0;
    std::set<Point> antinodes {};
    for (auto& [c, val]: t.antennas) {
        if (val.size() < 2) {
            continue;
        }
        for (size_t i = 0; i < val.size() - 1; i++) {
            for (size_t j = i + 1; j < val.size(); j++) {
                auto points = t.counter_antennas(val[i], val[j]);
                if (t.bounded(points.first)) {
                    antinodes.emplace(points.first);
                }
                if (t.bounded(points.second)) {
                    antinodes.emplace(points.second);
                }
            }
        }
    }
    count = antinodes.size();

    ::printf("Task 1 result: %zu\n", count);
    return 0;
}

