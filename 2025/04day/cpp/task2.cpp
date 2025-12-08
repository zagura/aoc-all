/*
 * =====================================================================================
 *
 *       Filename:  task2.cpp
 *
 *    Description:  AoC 2025 - Day 4
 *
 *        Version:  1.0
 *        Created:  8.12.2025
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */


#include <iostream>
#include <fstream>
#include <sstream>
#include <string_view>
#include <vector>
#include <cinttypes>
#include <format>
#include <print>
#include <map>

bool fit(ssize_t i, ssize_t limit) {
    return (0 <= i and i < limit);
}
bool empty(ssize_t i, ssize_t j, const std::vector<std::string>& data) {
    return (!fit(i, data.size()) or !fit(j, data[0].size()) or data[i][j] == '.');
}
bool filled(ssize_t i, ssize_t j, const std::vector<std::string>& data) {
    return (not empty(i, j, data));
}


int remove(std::vector<std::string>& data) {
    size_t total = 0;
    std::vector<std::string> forklift(data);
    for(ssize_t i = 0; i < data.size(); i++) {
        for(ssize_t j = 0; j < data[0].size(); j++) {
            if (empty(i, j, data)) {
                continue;
            }
            size_t count = 0;
            for (auto di: {-1, 0, 1 }) {
                for (auto dj:  {-1, 0, 1}) {
                    if (di != 0 or dj != 0) {
                        // std::println("D: [{}, {}], [{}, {}] : {}", i, j, (i+di), (j+dj), (filled(i+di, j+dj, data) ? "@" : "."));
                        count += filled(i + di, j + dj, data) ? 1 : 0;
                    }
                }
            }
            if (count < 4) {
                forklift[i][j] = '.';
                std::println("({}, {}) -> {}", i, j, count);
                total += 1;
            }
        }
    }
    data = forklift;
    return total;
}


int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    std::vector<std::string> data {};
    for (std::string line; getline(input, line);) {
        if (line.size() <= 1) {
            continue;
        }
        data.push_back(line);
    }
    size_t total = 0;
    size_t run_count = 0;
    do {
        run_count = 0;
        run_count = remove(data);
        total += run_count;
    } while (run_count > 0);
    ::printf("Task 2 result: %" PRIu64 "\n", total);
    return 0;
}
