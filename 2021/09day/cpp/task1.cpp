/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2021 - Day 9
 *
 *        Version:  0.1.0
 *        Created:  09.12.2021
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

static std::array<int, 4> delta_x = { -1, 1, 0, 0 };
static std::array<int, 4> delta_y = { 0, 0, -1, 1 };


size_t lowest_points(const std::vector<std::vector<int>>& points) {
    size_t total_lowest = 0;
    for (size_t x = 0; x < points.size(); x++) {
        for (size_t y = 0; y < points[x].size(); y++) {
            bool is_low = true;
            for (size_t di = 0; di < delta_x.size(); di++) {
                int new_x = x + delta_x[di];
                int new_y = y + delta_y[di];
                if (new_x >= 0 && new_x < static_cast<int>(points.size())) {
                    if (new_y >= 0 && new_y < static_cast<int>(points[new_x].size())) {
                        is_low = is_low && (points[x][y] < points[new_x][new_y]);
                    }
                }
            }
            if (is_low) {
//                printf("low_point (%zu, %zu): %d\n", x, y, points[x][y]);
                total_lowest += (1 + points[x][y]);
            }
        }
    }
    return total_lowest;
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
    size_t result = 0;
    std::vector<std::vector<int>> heightmap {};
    size_t line_no = 0;
    for (std::string line; getline(input, line); ) {
        if (line.size() > 0) {
            heightmap.push_back(std::vector<int>());
            heightmap.reserve(line.size());
        }
        for (const char& c: line) {
            if (c >= '0' && c <= '9') {
                heightmap[line_no].push_back(c - '0');
            }
        }
        line_no++;
    }
    result = lowest_points(heightmap);
    ::printf("Task 1 result: %zu\n", result);
    return 0;
}

