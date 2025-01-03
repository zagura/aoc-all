/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2024 - Day 18
 *
 *        Version:  0.1.0
 *        Created:  03.01.2025
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
#include <vector>
#include <cinttypes>
#include <cctype>
#include <variant>
#include <print>
#include <set>
#include <queue>

using std::string;
using std::vector;
using std::array;
using std::map;
using std::stringstream;

// static constexpr int SIZE = 7;
// static constexpr int LIMIT = 12;
static constexpr int SIZE = 71;
static constexpr int LIMIT = 1024;

using DataMap = std::array<std::array<bool, SIZE>, SIZE>;
using Point = std::pair<int, int>;
using CharMap = std::array<std::string, SIZE>;
CharMap char_map {};
bool inside(Point p, int size) {
    return (p.first >= 0 && p.first < size) &&
           (p.second >= 0 && p.second < size);
}

int walk_bfs(const DataMap& graph, Point s) {
    std::set<Point> visited {};
    std::map<Point, size_t> distances {};
    std::queue<std::pair<Point, size_t>> to_visit;
    to_visit.emplace(s, 0);
    while (!to_visit.empty()) {
        auto current = to_visit.front();
        to_visit.pop();
        if (not visited.contains(current.first)) {
            visited.insert(current.first);
            distances[current.first] = current.second;
            std::array<Point, 4> diffs = {{{ -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1}}};
            for (auto [dx, dy]: diffs) {
                Point p = { current.first.first + dx, current.first.second + dy };
                if (inside(p, SIZE)) {
                    if (not graph[p.first][p.second]) {
                        to_visit.emplace(p, current.second + 1);
                        char_map[p.first][p.second] = 'O';
                    }
                }
            }
        }
    }
    for (auto& l: char_map) {
        std::println("{}", l);
    }
    Point end = { SIZE - 1, SIZE - 1 };
    return distances.at(end);
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
    size_t line_no = 0;
    std::array<std::array<bool, SIZE>, SIZE> data {};
    std::string line_template = "";
    for (size_t i = 0; i < SIZE; i++) {
        line_template += '.';
    }
    for (auto& l: char_map) {
        l = line_template;
    }
    for (string line; getline(input, line); line_no++) {
        stringstream ss { line };
        int a, b;
        char c;
        ss >> a >> c >> b;
        std::print("({}, {})\n", a, b);
        data[b][a] = true;
        char_map[b][a] = '#';
        for (auto& l: char_map) {
            std::println("{}", l);
        }
        if (line_no == LIMIT) {
            break;
        }
    }

    std::println("Task 1 result: {} ", walk_bfs(data, {0, 0}));
    return 0;
}

