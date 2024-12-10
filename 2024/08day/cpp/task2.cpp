/*
 * =====================================================================================
 *
 *       Filename:  task2.cpp
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
#include <list>

using Point = std::pair<int, int>;

class Task {
public:
    int size {};
    bool bounded(const std::pair<int, int>& coords) const;
    std::vector<std::string> data {};
    std::map<char, std::vector<std::pair<int, int>>> antennas {};
    std::list<Point> antinodes(const Point& a, const Point& b);
    void print() const ;
    void fill(const std::set<Point>& points);
};

void Task::print() const {
    for (auto d: data) {
        std::println("{}", d);
    }
}

void Task::fill(const std::set<Point>& points) {
    for (const auto& [x, y]: points) {
        data[x][y] = '#';
    }
}

bool Task::bounded(const std::pair<int, int>& coords) const {
    return coords.first >= 0 && coords.first < static_cast<int>(data.size())
    && coords.second >= 0  && coords.second < static_cast<int>(data.begin()->size());
}

int gcd(int left, int right) {
    int greater = left;
    int lower = right;
    if (lower >= greater) {
        std::swap(greater, lower);
    }
    if (lower == 0) {
        return greater;
    }
    while (greater != lower && greater % lower != 0) {
        int tmp = greater % lower;
        greater = lower;
        lower = tmp;
    }
    return lower;
}

std::list<Point> Task::antinodes(const Point& a, const Point& b) {
    int dx = b.first - a.first;
    int dy = b.second - a.second;
    auto denominator = gcd(dx, dy);
    int d_x = dx / denominator;
    int d_y = dy / denominator;
    std::list<Point> points {};
    // Point between a and b
    for (int i = 1; i < denominator; i++) {
        Point p = { a.first + (i * d_x), a.second + (i * d_y) };
        if (bounded(p)) {
            points.push_back(p);
        } else {
            break;
        }
    }
    for (int i = 1; i < size; i++) {
        Point p = { b.first + (i * d_x), b.second + (i * d_y) };
        if (bounded(p)) {
            points.push_back(p);
        } else {
            break;
        }
    };
    for (int i = 1; i < size; i++) {
        Point p = { a.first - (i * d_x), a.second - (i * d_y) };
        if (bounded(p)) {
            points.push_back(p);
        } else {
            break;
        }
    };
    return points;
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
    t.size = std::max(t.data.size(), t.data.begin()->size());
    std::set<Point> antinodes {};
    for (auto& [c, val]: t.antennas) {
        if (val.size() < 2) {
            continue;
        }
        for (size_t i = 0; i < val.size() - 1; i++) {
            for (size_t j = i + 1; j < val.size(); j++) {
                auto points = t.antinodes(val[i], val[j]);
                for (auto& p: points) {
                    antinodes.emplace(p);
                }
            }
        }
        if (val.size() > 2) {
            for (auto& p: val) {
                antinodes.insert(p);
            }
        }
    }
    count = antinodes.size();
    Task t2 = t;
    t2.fill(antinodes);
    t.print();
    std::print("\nAfter:\n\n");
    t2.print();
    ::printf("Task 2 result: %zu\n", count);
    return 0;
}

