/*
 * =====================================================================================
 *
 *       Filename:  task2.cpp
 *
 *    Description:  Advent of Code 2021 - Day 17
 *
 *        Version:  0.1.0
 *        Created:  17.12.2021
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

std::pair<std::pair<int, int>, std::pair<int, int>> get_points(std::string& line) {
    // format: "target area: x=x1..x2 y=y1..y2"
    string xs = line.substr(line.find('x') + 2);
    int y_sep = xs.find('y');
    string ys = xs.substr(y_sep + 2);
    xs = xs.substr(0, y_sep - 1);
    std::pair<int, int> x {}, y {};
    x.first = std::stoi(xs);
    x.second = std::stoi(xs.substr(xs.find_last_of('.') + 1));
    printf("Xs: %d , %d\n", x.first, x.second);
    y.first = std::stoi(ys);
    y.second = std::stoi(ys.substr(ys.find_last_of('.') + 1));
    printf("Ys: %d , %d\n", y.first, y.second);
    return std::make_pair(x, y);
}

int gauss(int m) {
    return (m * (m + 1) / 2);
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
    std::string line;
    getline(input, line);
    auto [x, y] = get_points(line);
    int x_vel {}, y_vel {};
    // Search for x which "stops" within x range

    size_t result = 0;
    // Brute force solution - check each reasonable velocity
    // Check each step if we don't miss it
    for (x_vel = 1; x_vel <= x.second; x_vel++) {
        for (y_vel = y.first; y_vel <= abs(y.first); y_vel++) {
            std::pair<int, int> vel = std::make_pair(x_vel, y_vel);
            std::pair<int, int> pos = std::make_pair(0, 0);
            for (int steps = 0; steps <= x.second * abs(y.first) * 2; steps++) {
                pos = make_pair(pos.first + vel.first, pos.second + vel.second);
                if (vel.first > 0) {
                    vel = make_pair(vel.first - 1, vel.second - 1);
                } else {
                    vel = make_pair(vel.first, vel.second - 1);
                }
                if (pos.first >= x.first && pos.first <= x.second) {
                    if (pos.second >= y.first && pos.second <= y.second) {
                        result++;
                        break;
                    }
                }
                // Too low and too far right
                if (pos.first > x.second && pos.second < y.first) {
                    break;
                }
            }
        }
    }
    printf("Task 2 result: %zu\n", result);
    return 0;
}

