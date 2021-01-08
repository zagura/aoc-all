/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2020 - Day 13
 *
 *        Version:  0.1.0
 *        Created:  13.12.2020
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
#include <unordered_map>
#include <vector>

using std::string;
using std::vector;
using std::array;
using std::map;
using std::stringstream;
constexpr size_t kRoundCount = 30 * 1000 * 1000;

int play_game(vector<int> numbers, size_t round_count) {
    std::unordered_map<int, std::pair<int, int>> usages {};
    usages.reserve(round_count + 1);
    // Prepare
    for (size_t round = 0; round < numbers.size(); round++) {
        usages[numbers[round]] = std::make_pair(-1, round + 1);
    }
    for (size_t round = numbers.size() + 1; round < round_count + 5; round++) {
        int number = numbers.back();
        auto [previous_use, previous_round] = usages.at(number);
        int next_number = 0;
        if (previous_use != -1) {
            next_number = round - previous_use - 1;
        }
        numbers.push_back(next_number);
        if (usages.find(next_number) != usages.end()) {
            usages[next_number] = std::make_pair(usages[next_number].second, round);
        } else {
            usages[next_number] = std::make_pair(-1, round);
        }
    }
    return numbers.at(round_count - 1);
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
    vector<int> numbers;
    numbers.reserve(2020);
    for (string line; getline(input, line, ','); ) {
        int n = std::stoi(line);
        numbers.push_back(n);
    }
    result = play_game(numbers, 2020);
    int result2 = play_game(numbers, kRoundCount);

    ::printf("Task 1 result: %d\n", result);
    ::printf("Task 2 result: %d\n", result2);
    return 0;
}

