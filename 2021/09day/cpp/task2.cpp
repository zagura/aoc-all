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
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
#include <queue>
#include <list>

static std::array<int, 4> delta_x = { -1, 1, 0, 0 };
static std::array<int, 4> delta_y = { 0, 0, -1, 1 };

bool is_lowest(const std::vector<std::vector<int>>& points, const size_t x, const size_t y) {
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
    return is_low;
}

size_t lowest_points(const std::vector<std::vector<int>>& points) {
    size_t total_lowest = 0;
    for (size_t x = 0; x < points.size(); x++) {
        for (size_t y = 0; y < points[x].size(); y++) {
            if (is_lowest(points, x, y)) {
                total_lowest += (1 + points[x][y]);
            }
        }
    }
    return total_lowest;
}
// DFS for searching point map
size_t basin_size(const std::vector<std::vector<int>>& points, size_t start_x, size_t start_y) {
    std::list<std::pair<size_t, size_t> > next_points {};
    std::set<std::pair<size_t, size_t>> visited {};
    next_points.emplace_back(start_x, start_y);
    size_t total_size = 0;
    while (!next_points.empty()) {
        std::pair<size_t, size_t> current = next_points.back();
        next_points.pop_back();
        if (!visited.contains(current)) {
            visited.insert(current);
            total_size += 1; // points[current.first][current.second];
            for (size_t di = 0; di < delta_x.size(); di++) {
                int new_x = current.first + delta_x[di];
                int new_y = current.second + delta_y[di];
                if (new_x >= 0 && new_x < static_cast<int>(points.size())) {
                    if (new_y >= 0 && new_y < static_cast<int>(points[new_x].size())) {
                        if (points[new_x][new_y] < 9) {
                            next_points.emplace_back(new_x, new_y);
                        }
                    }
                }
            }
        }
    }
    return total_size;
}

size_t total_basins(const std::vector<std::vector<int>>& points) {
    std::vector<size_t> basins {};
    for (size_t x = 0; x < points.size(); x++) {
        for (size_t y = 0; y < points[x].size(); y++) {
            if (is_lowest(points, x, y)) {
                basins.push_back(basin_size(points, x, y));
            }
        }
    }
    std::sort(basins.begin(), basins.end());
    size_t bsize = basins.size() - 1;
    printf("Largest basins %zu, %zu, %zu\n",
           basins[bsize], basins[bsize - 1], basins[bsize - 2]);
    return basins[bsize] * basins[bsize - 1] * basins[bsize - 2];
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
    result = total_basins(heightmap);
    ::printf("Task 2 result: %zu\n", result);
    return 0;
}

