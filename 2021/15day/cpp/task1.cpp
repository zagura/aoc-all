/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2021 - Day 15
 *
 *        Version:  0.1.0
 *        Created:  15.12.2021
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
#include <vector>
#include <queue>
#include <map>
#include <set>

using std::string;
using std::vector;
using std::array;
using std::stringstream;

const std::array<std::pair<int, int>, 4> neighbours = {{
//    { -1, -1 }, // upper-left
    { -1, 0 }, // up
//    { -1, 1 },  // upper-right
    { 0, -1 }, // left
    { 0, 1 },  // right
//    { 1, -1 },
    { 1, 0 },
//    { 1, 1}
}};
using std::string;
template <class T>
bool fits(const int& index, const T& vec) {
    return (index >= 0 && index < static_cast<int>(vec.size()));
}
using Path = std::pair<std::pair<size_t, size_t>, int>;

void print(const std::vector<std::vector<int>>& data) {
    for (auto& row: data) {
        for (auto& col: row) {
            printf("%d", col);
        }
        printf("\n");
    }
    printf("\n");
}

size_t dijkstra(const std::vector<std::vector<int>>& data) {
    std::pair<size_t, size_t> start = std::make_pair(0, 0);
    std::pair<size_t, size_t> end = std::make_pair(data.size() - 1, data.back().size() - 1);
    std::set<std::pair<size_t, size_t>> visited {};
    auto comp = [](const Path& p1, const Path& p2) { return (p1.second > p2.second); };
    std::vector<Path> container {};
    std::priority_queue<Path, std::vector<Path>, decltype (comp)> next {comp, container};
    next.emplace(start, 0);
//    print(data);
    while (!next.empty()) {
        Path current = next.top();
        next.pop();
        if (!visited.contains(current.first)) {
            if (current.first == end) {
                printf("Visit (%zu, %zu) with value (%d) path_len %d\n", current.first.first,
                   current.first.second,
                   data[current.first.first][current.first.second],
                   current.second);
                return current.second;
            }
            visited.emplace(current.first);
            auto& coords = current.first;
            for (const auto& [dx, dy]: neighbours) {
                if (fits(coords.first + dx, data) &&
                    fits(coords.second + dy, data[coords.first + dx])) {
                        next.emplace(std::make_pair(coords.first + dx, coords.second + dy),
                                 current.second + data[coords.first + dx][coords.second + dy]);
                }
            }
        }
    }

    return 0;
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
    std::vector<std::vector<int>> data_map;
    data_map.reserve(100);
    size_t line_no = 0;
    for (string line; getline(input, line);) {
        if (line.size() > 0) {
            data_map.emplace_back(std::vector<int>());
            for (auto& c: line) {
                data_map[line_no].push_back(c - '0');
            }
            line_no++;
        }
    }
    ::printf("Task 1 result: %zu\n", dijkstra(data_map));
    return 0;
}

