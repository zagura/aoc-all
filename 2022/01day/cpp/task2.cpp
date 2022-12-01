/*
 * =====================================================================================
 *
 *       Filename:  task2.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01.12.2022 07:12
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string_view>
#include <vector>
#include <cinttypes>
#include <fmt/format.h>
#include <map>

int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    uint64_t cals {};
    std::vector<uint64_t> elves_cals;
    int elf_id = 0;
    uint64_t max_cals = 0;
    for (std::string line; getline(input, line);) {
        if (line.empty()) {
            elves_cals.push_back(cals);
            elf_id++;
            cals = 0;
        }
        std::stringstream stream { line };
        int current_cals = 0;
        stream >> current_cals;
        cals += current_cals;
    }
    std::sort(elves_cals.begin(), elves_cals.end());
    uint64_t result = 0;
    if (elves_cals.size() > 3) {
        size_t len = elves_cals.size() - 1;
        result += elves_cals[len];
        result += elves_cals[len - 1];
        result += elves_cals[len - 2];
    }
    ::printf("Task 2 result: %" PRIu64 "\n", result);
    return 0;
}
