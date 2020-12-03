/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:i Day 3 Advent of Code 2020
 *
 *        Version:  0.1.0
 *        Created:  03.12.2020
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using std::string;
using std::vector;

size_t run_map(size_t right_move, size_t down_move,  vector<string>& tree_map) {
    size_t tree_count = 0;
    size_t current_x = 0;
    size_t current_y = 0;
    const size_t last = tree_map.size();
    const size_t horizontal_len = tree_map.at(0).size();
    ::printf("horizontal_len: %zu", horizontal_len);
    while (current_y < last - down_move) {
        current_x = (current_x + right_move) % horizontal_len;
        current_y += down_move;
        if (tree_map[current_y][current_x] == '#') {
            tree_count++;
        }
        ::printf("X: %zu Y: %zu TC: %zu (%c)\n", current_x, current_y,
                 tree_count, tree_map[current_y][current_x]);
    }
    ::printf("Task 1 result is: %zu\n", tree_count);
    return tree_count;
}

int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    std::vector<std::string> tree_map {};
    for (std::string line; getline(input, line);) {
        if (line == "\n") {
            // Skip empty line
            continue;
        }
        tree_map.push_back(line);
    }
    size_t total_count = 1;
    total_count *= run_map(1, 1, tree_map);
//    total_count *= run_map(3, 1, tree_map);
//    total_count *= run_map(5, 1, tree_map);
//    total_count *= run_map(7, 1, tree_map);
//    total_count *= run_map(1, 2, tree_map);

    ::printf("Task 2: %zu \n", total_count);

    return 0;
}
