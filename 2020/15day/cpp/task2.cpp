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

int play_game(vector<int> numbers, int round_count) {
    std::unordered_map<int, std::pair<int, int>> usages {};
    // Prepare
    for (size_t round = 0; round < numbers.size(); round++) {
        usages[numbers[round]] = std::make_pair(-1, round + 1);
    }
    for (int round = numbers.size() + 1; round < round_count + 5; round++) {
        int number = numbers.back();
        if (usages.find(number) != usages.end()) {
            auto [previous_use, previous_round] = usages.at(number);
//            printf("round: %d: n = %d, prev = %d\n", round, number, previous_use);
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

        } else {
            printf("round: %d: n = %d, prev = %d\n", round, number, -1);
            int next_number = 0;
            numbers.push_back(next_number);
            if (usages.find(next_number) != usages.end()) {
                usages[next_number] = std::make_pair(usages[next_number].second, round);
            } else {
                usages[next_number] = std::make_pair(-1, round);
            }
        }
    }
    for (size_t r = round_count - 5; r < numbers.size(); r++) {
        printf("n[%zu] = %d\n", r, numbers.at(r));
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
    int result2 = play_game(numbers, 30000000);
/*  while (input >> dat) {
        arr.push_back(data);
    }
*/

    ::printf("Task 1 result: %d\n", result);
    ::printf("Task 1 result: %d\n", result2);
    return 0;
}

