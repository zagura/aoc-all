/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2021 - Day 7
 *
 *        Version:  0.1.0
 *        Created:  07.12.2021
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


int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    if (!input.good()) {
        ::fprintf(stderr, "Cannot open input file\n");
        return 2;
    }
    std::vector<int> positions {};
    int min_value = 0;
    int max_value = 0;
    std::string element;
    getline(input, element, ',');
    int value = std::stoi(element);
    positions.push_back(value);
    min_value = max_value = value;
    while(getline(input, element, ',')) {
        value = std::stoi(element);
        if (value < min_value) {
            min_value = value;
        }
        if (value > max_value) {
            max_value = value;
        }
        positions.push_back(value);
    }
    size_t min_fuel = std::numeric_limits<size_t>::max();
    int best_pos = min_value;
    for (int i = min_value; i <= max_value; i++) {
        size_t total_fuel = 0;
        for (auto& v: positions) {
            total_fuel += std::abs(v - i);
        }
        if (total_fuel < min_fuel) {
            min_fuel = total_fuel;
            best_pos = i;
            printf("New min_fuel %zu for value %d\n", min_fuel, best_pos);
        }
    }
    ::printf("Task 1 result: %zu\n", min_fuel);
    return 0;
}

