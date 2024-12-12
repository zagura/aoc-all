/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2024 - Day 11
 *                  --- Day 11: Plutonian Pebbles ---
 *
 *        Version:  0.1.0
 *        Created:  12.12.2024
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <iostream>
#include <numeric>
#include <string>
#include <fstream>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <queue>
#include <algorithm>
#include <vector>
#include <format>
#include <cmath>



void blink(std::list<uint64_t>& stones) {
    for(auto s = stones.begin(); s != stones.end(); s++) {
        if (*s == 0) {
            *s = 1;
        } else {
            std::string rep = std::to_string(*s);
            if (rep.size() % 2 == 0) {
                uint64_t div = 1;
                for (size_t i = 0; i < rep.size() / 2; i++) {
                    div *= 10;
                }
                stones.insert(s, *s / div);
                *s %= div;
            } else {
                *s *= 2024;
            }
        }
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
    std::string line;
    std::getline(input, line);
    std::list<uint64_t> stones {};
    std::stringstream ss { line };
    int n;
    while (ss >> n) {
        stones.push_back(n);
    }

    for (int i = 0; i < 25; i++) {
        blink(stones);
    }
    // result = std::accumulate(distances.begin(), distances.end(), 0);

    ::printf("Task 1 result: %zu\n", stones.size());
    return 0;
}

