/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  
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
#include <fmt/format.h>
#include <map>

int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    uint64_t cals {};
    std::map<int, uint64_t> elves_cals;
    int elf_id = 0;
    uint64_t max_cals = 0;
    for (std::string line; getline(input, line);) {
        if (line.empty()) {
            elves_cals[elf_id] = cals;
            if (cals > max_cals) {
                max_cals = cals;
            }
            elf_id++;
            cals = 0;
        }
        std::stringstream stream { line };
        int current_cals = 0;
        stream >> current_cals;
        cals += current_cals;
    }
    ::printf("Task 1 result: %" PRIu64 "\n", max_cals);
    return 0;
}
