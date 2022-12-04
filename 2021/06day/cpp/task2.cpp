/*
 * =====================================================================================
 *
 *       Filename:  task2.cpp
 *
 *    Description:  Advent of Code 2021 - Day 6
 *
 *        Version:  0.1.0
 *        Created:  06.12.2021
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */

#include <array>
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <cinttypes>

constexpr int days = 256;
void print_fishes(const std::array<uint64_t, 10>& fishes) {
    uint64_t sum = 0;
    for (auto& f: fishes) {
        printf("%zu,", f);
        sum += f;
    }
    printf("sum: %" PRIu64 "\n", sum);

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
    std::array<uint64_t, 10> fishes {};
    for (std::string line; getline(input, line, ','); ) {
        if (line.size() > 0) {
            int days_val = std::stoi(line);
            fishes[days_val]++;
        }
    }
    print_fishes(fishes);
    for (int d = 0; d < days; d++) {
        printf("Day %d: \n\t", d);
        uint64_t zeros = fishes[0];
        for (uint64_t i = 0; i <fishes.size() - 1; i++) {
            fishes[i]=fishes[i+1];
        }
        fishes[6] += zeros;
        fishes[8] = zeros;
        print_fishes(fishes);
    }

    uint64_t result = 0;
    for (auto& f: fishes) { result += f; }
    ::printf("Task 1 result: %" PRIu64 "\n", result);
    return 0;
}

