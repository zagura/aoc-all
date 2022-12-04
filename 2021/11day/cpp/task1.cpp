/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2020 - Day 11
 *
 *        Version:  0.1.1
 *        Created:  11.12.2020
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <array>
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
#include <queue>
#include <algorithm>

const std::array<std::pair<int, int>, 8> neighbours = {{
    { -1, -1 }, // upper-left
    { -1, 0 }, // up
    { -1, 1 },  // upper-right
    { 0, -1 }, // left
    { 0, 1 },  // right
    { 1, -1 },
    { 1, 0 },
    { 1, 1}
}};

using std::string;
template <class T>
bool fits(const int& index, const T& vec) {
    return (index >= 0 && index < static_cast<int>(vec.size()));
}
void step(std::vector<std::vector<int>>& data, /* inout */ size_t& flash_count) {
    std::set<std::pair<size_t, size_t>> flashed {};
    std::queue<std::pair<size_t, size_t>> to_flash{};
    // Part 1
    for (size_t row = 0; row < data.size(); row++) {
        for(size_t column = 0; column  < data[row].size(); column++) {
            data[row][column] = data[row][column] + 1;
            if (data[row][column] > 9) {
//                printf("Put new element (%zu, %zu) = %d\n", row, column, data[row][column]);
                to_flash.emplace(row, column);
            }
        }
    }
    // Part 2
    while (!to_flash.empty()) {
        auto location = to_flash.front();
//        printf("To flash pop: (%zu, %zu)\n", location.first, location.second);
        to_flash.pop();
        if (flashed.contains(location)) {
            // already flashed one
            continue;
        }
//        printf("Flashing %zu, %zu\n", location.first, location.second);
        flashed.insert(location);
        for (const auto& el: neighbours) {
            int new_row = location.first + el.first;
            int new_column = location.second + el.second;
            if (fits(new_row, data) && fits (new_column, data[new_row])) {
                data[new_row][new_column] += 1;
                if (data[new_row][new_column] > 9) {
                    auto new_loc = std::make_pair(new_row, new_column);
                    if (!flashed.contains(new_loc)) {
                        to_flash.push(new_loc);
                    }
                }
            }
        }
    }
    // Part 3
    for (size_t row = 0; row < data.size(); row++) {
        for(size_t column = 0; column  < data[row].size(); column++) {
            if (data[row][column] > 9) {
                data[row][column] = 0;
                flash_count++;
            }
        }
    }
    printf("After\n");
    for(auto& r: data) {
        for (auto& el: r) {
            if (el == 0) {
                printf("\e[1;31m%d\033[0m", el);
            } else {
                printf("%d", el);
            }

        }
        printf("\n");
    }
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
    std::vector<std::vector<int>> data {};
    size_t flash_count {};
    size_t line_no = 0;

    for (std::string line; getline(input, line); line_no++) {
        if (line.size() > 0) {
            data.push_back(std::vector<int>{});
            for (auto c: line) {
                if (c >= '0' && c <= '9') {
                    data[line_no].push_back(static_cast<int>(c - '0'));
                }
            }
        }
    }

    for (size_t it = 0; it < 100; it++) {
        printf("After step %zu\n", it + 1);
        step(data, flash_count);
    }
    ::printf("Task 1 result: %zu\n", flash_count);
    return 0;
}

