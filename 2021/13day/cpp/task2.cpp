/*
 * =====================================================================================
 *
 *       Filename:  task2.cpp
 *
 *    Description:  Advent of Code 2021 - Day 13
 *
 *        Version:  0.1.0
 *        Created:  13.12.2021
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
#include <list>
#include <map>
#include <vector>
#include <set>

using std::string;
using std::vector;
using std::array;
using std::map;
using std::stringstream;

std::set<std::pair<int, int>> fold(std::set<std::pair<int, int>> points,
                                   std::list<std::pair<char, int>>& fold_list) {
    auto [direction, mark] = fold_list.front();
    std::set<std::pair<int, int>> folded_points{};
    if (direction == 'x') {
        for (const auto& [x, y]: points) {
            if (x < mark) {
                folded_points.emplace(x, y);
            } else {
                folded_points.emplace(mark - (x - mark), y);
            }
        }
    } else if (direction == 'y') {
        for (const auto& [x, y]: points) {
            if (y < mark) {
                folded_points.emplace(x, y);
            } else {
                folded_points.emplace(x, (mark - (y - mark)));
            }
        }
    }
    fold_list.pop_front();
    return folded_points;
}

void print(const std::set<std::pair<int, int>>& points) {
    int max_x = 0;
    int max_y = 0;
    for (const auto& [x, y]: points) {
        if (x > max_x) {
            max_x = x;
        }
        if (y > max_y) {
            max_y = y;
        }
    }
    for (int y = 0; y <= max_y; y++) {
        for(int x = 0; x <= max_x; x++) {
            if (points.contains(std::make_pair(x, y))) {
                printf("#");
            } else {
                printf(".");
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

    bool folds = false;
    std::set<std::pair<int, int>> points {};
    std::list<std::pair<char, int>> fold_list {};
    for (string line; getline(input, line); ) {
        if (line.size() == 0) {
            folds = true;
            continue;
        }
        stringstream line_stream { line };
        if (!folds) {
            string coord {};
            getline(line_stream, coord, ',');
            int x = stoi(coord);
            getline(line_stream, coord);
            int y = stoi(coord);
            points.emplace(x, y);
        } else {
            string token {};
            getline(line_stream, token, '=');
            char direction = token.back();
            getline(line_stream, token);
            int val = stoi(token);
            fold_list.emplace_back(direction, val);
        }
    }
    while (!fold_list.empty()) {
        points = fold(points, fold_list);
    }
    print(points);
//    ::printf("Task 1 result: %zu\n", points.size());
    return 0;
}

