/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2021 - Day 14
 *
 *        Version:  0.1.0
 *        Created:  14.12.2021
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
#include <iomanip>
#include <bitset>
using std::string;
using std::vector;
using std::array;
using std::map;
using std::stringstream;

std::string spawn(const std::string& polymer, const std::map<std::pair<char, char>, char>& rules) {
    std::string new_polymer {};
    new_polymer.push_back(polymer[0]);
    for (size_t left = 0; left < polymer.size() - 1; left++) {
        new_polymer.push_back(rules.at(std::make_pair(polymer[left], polymer[left + 1])));
        new_polymer.push_back(polymer[left + 1]);
    }
    return new_polymer;
}

size_t part1(const std::string& polymer) {
    std::map<char, size_t> freqs {};
    for (auto& c: polymer) {
        freqs[c]++;
    }
    size_t min_count = freqs.begin()->second;
    size_t max_count = min_count;
    for (auto& el: freqs) {
        if (el.second > max_count) {
            max_count = el.second;
        }
        if (el.second < min_count) {
            min_count = el.second;
        }
    }
    return max_count - min_count;
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

    std::string start_polymer;
    getline(input, start_polymer);
    std::map<std::pair<char, char>, char> rules {};
    for (std::string line; getline(input, line); ) {
        if (line.size() == 7) {
            rules.emplace(std::make_pair(line[0], line[1]), line.back());
        }
    }
    std::string polymer = start_polymer;
    for (int i = 0; i < 10; i++) {
        polymer = spawn(polymer, rules);
    }


    ::printf("Task 1 result: %zu\n", part1(polymer));
    return 0;
}

