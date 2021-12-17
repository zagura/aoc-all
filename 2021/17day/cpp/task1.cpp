/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
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
    std::pair<int, int> double_x = make_pair(2 * x.first, 2 * x.second);
    for (x_vel = 1; x_vel <= (x.first + x.second) / 4; x_vel++) {
        int target_x = x_vel * (x_vel + 1);
        if (double_x.first <=  target_x && double_x.second >= target_x) {
            printf("X velocity: %d\n", x_vel);
            break;
        }
    }
    // Search for max y that will be in area within at least x_vel steps.
    // The "fastest y velocity" is when it fits y area
    for (int tmp_y = 1; tmp_y < abs(y.first) * 2; tmp_y++) {
        // vel_y, vel_y - 1, ... , 0 -> (0 + vel_y) / 2 * (vel_y + 1)
        int max_y = gauss(tmp_y);
        auto diff_y = make_pair(max_y - y.first, max_y - y.second);
        for (int steps = x_vel; steps < abs(y.first); steps++) {
            // I really don't know why steps + 1 instead of steps :/
            int min_y = gauss(steps + 1);
            if (min_y >= diff_y.second && min_y <= diff_y.first) {
                if (tmp_y > y_vel) {
                    y_vel = tmp_y;
                    printf("Possible highest position %d\n", max_y);
                }
            }
//            if (min_y > diff_y.first) {
//                break;
//            }
        }
    }
    return 0;
}

