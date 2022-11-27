/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2021 - Day 22
 *
 *        Version:  0.1.0
 *        Created:  22.12.2021 - 23.02.2022
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
#include <unordered_map>

using std::string;
using std::vector;
using std::array;
using std::map;
using std::pair;
using std::make_pair;
using std::stringstream;
struct Point3D {
    Point3D(int X, int Y, int Z) noexcept: x(X), y(Y), z(Z)  {}
    int x = 0;
    int y = 0;
    int z = 0;
    bool operator==(const Point3D& other) {
        return (other.x == x)
               and (other.y == y)
               and (other.z == z);
    }
};

struct Area3D {
    std::pair<int, int> x_range {};
    std::pair<int, int> y_range {};
    std::pair<int, int> z_range {};
    bool action = false; // off
    Area3D(std::pair<int, int> range_x, std::pair<int, int> range_y, std::pair<int, int> range_z, bool on)
        : x_range(range_x), y_range(range_y), z_range(range_z), action(on) {}
};



std::pair<int, int> parse_coords(std::string str) {
    std::stringstream stream { str };
    std::string token;
    getline(stream, token, '=');
    getline(stream, token, '.');
    int first = std::stoi(token);
    getline(stream, token);
    int second = std::stoi(token.substr(1));
    return std::make_pair(first, second);
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
    int result = 0;

    std::vector<Area3D> data;
    data.reserve(500);
    for (string line; getline(input, line); ) {
        if (line.empty()) { continue; } // skip empty lines
        std::string token;
        std::stringstream line_stream { line };
        std::string action;
        getline(line_stream, action, ' ');
        getline(line_stream, token, ',');
        auto range_x = parse_coords(token);
        getline(line_stream, token, ',');
        auto range_y = parse_coords(token);
        getline(line_stream, token, ',');
        auto range_z = parse_coords(token);
        data.emplace_back(range_x, range_y, range_z, action == "on");
    }
    for (auto& el: data) {
        printf("(%d, %d, %d) -> (%d, %d, %d): %s\n", el.x_range.first, el.y_range.first, el.z_range.first,
               el.x_range.second, el.y_range.second, el.z_range.second, el.action ? "on" : "off");
    }
    std::vector<std::vector<std::vector<bool>>> area {};
    area.resize(102);
    for (auto &surface: area) {
        surface.resize(102);
        for (auto& el: surface) {
            el.resize(102);
        }
    }
    result = static_cast<int>(data.size());
    for (auto& el: data) {
        for (auto x = std::max(-50, el.x_range.first); x <= std::min(50, el.x_range.second); x++) {
            for (auto y = std::max(-50, el.y_range.first); y <= std::min(50, el.y_range.second); y++) {
                for (auto z = std::max(-50, el.z_range.first); z <= std::min(50, el.z_range.second); z++) {
                    area[x + 50][y + 50][z + 50] = el.action;
                }
            }
        }
    }
    size_t total = 0;
    for (auto &surface: area) {
        for (const auto& el: surface) {
            for (const auto &val: el) {
                total += (val ? 1 : 0);
            }
        }
    }

    ::printf("Task 1 result: %zu\n", total);
    return 0;
}
