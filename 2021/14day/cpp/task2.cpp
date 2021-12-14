/*
 * =====================================================================================
 *
 *       Filename:  task2.cpp
 *
 *    Description:  Advent of Code 2021 - Day 14
 *
 *        Version:  0.1.1
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

constexpr int step_count = 40;

std::map<std::pair<char, char>, size_t> spawn(const std::map<std::pair<char, char>, size_t>& polymer,
                                              const std::map<std::pair<char, char>, char>& rules) {
    std::map<std::pair<char, char>, size_t> new_polymer {};
    for(auto& [el, count]: polymer) {
        auto middle = rules.at(el);
        new_polymer[std::make_pair(el.first, middle)] += count;
        new_polymer[std::make_pair(middle, el.second)] += count;
    }
    return new_polymer;
}

size_t part2(const std::map<std::pair<char, char>, size_t>& polymer,
             std::string& start_polymer) {
    std::map<char, size_t> freqs {};
    for (auto& [el, count]: polymer) {
        freqs[el.first] += count;
        freqs[el.second]+= count;
    }
    freqs[*start_polymer.begin()]++;
    freqs[start_polymer.back()]++;
    for (auto& e: freqs) {
        e.second /= 2;
    }

    size_t min_count = freqs.begin()->second;
    size_t max_count = min_count;
    printf("Start %c: %zu\n", freqs.begin()->first, min_count);
    for (auto& el: freqs) {
        if (el.second > max_count) {
            max_count = el.second;
            printf("Most frequent: %c: %zu\n", el.first, el.second);
        }
        if (el.second < min_count) {
            min_count = el.second;
            printf("least frequent: %c: %zu\n", el.first, el.second);
        }
    }
    return (max_count - min_count);
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
    std::map<std::pair<char, char>, size_t> polymer {};
    for (size_t i = 0; i < start_polymer.size() - 1; i++) {
        polymer[std::make_pair(start_polymer[i], start_polymer[i + 1])]++;
    }
    printf("Step...");
    for (int i = 0; i < step_count; i++) {
        printf("%d\t", i);
        polymer = spawn(polymer, rules);
    }
    printf("\n");

    ::printf("Task 2 result: %zu\n", part2(polymer, start_polymer));
    return 0;
}

