/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2020 - Day 10
 *
 *        Version:  0.1.0
 *        Created:  11.12.2020
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
#include <algorithm>


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
    int jolts {};
    std::vector<int> jolts_converters {};
    jolts_converters.reserve(1000);
    jolts_converters.push_back(0);
    while (input >> jolts) {
        jolts_converters.push_back(jolts);
    }

    std::vector<int> diffs = jolts_converters;
    std::sort(diffs.begin(), diffs.end());
    for (auto d: diffs) {
        printf("%d\n", d);
    }
    int sum_ones = 0;
    int sum_threes = 0;
    diffs.push_back(diffs.back() + 3);
    // Part 1
    for (auto i = 1; i < diffs.size(); i++) {
        auto diff = diffs[i] - diffs[i-1];
        if (diff == 1) {
            sum_ones += 1;
        } else if (diff == 3) {
            sum_threes += 1;
        }
    }
    // Part 2
    std::vector<long long int> arrangements;
    arrangements.resize(diffs.size());
    arrangements[0] = 1;
    for (size_t i = 0; i < diffs.size() - 1; i++) {
        for (auto j = i + 1; j < diffs.size(); j++) {
            auto diff = diffs[j] - diffs[i];
            if (diff > 0 and diff <= 3) {
                arrangements[j] += arrangements[i];
            }
        }
    }
    ::printf("Ones: %d Threes: %d\n", sum_ones, sum_threes);
    ::printf("Task 1 result: %d\n", sum_ones * sum_threes);
    // Part 2
    ::printf("Task 2 result: %llu\n", arrangements.back());
    return 0;
}

