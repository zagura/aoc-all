/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Day 4 Advent of Code 2022
 *
 *        Version:  0.1.0
 *        Created:  04.12.2022
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map>

using std::string;
using std::vector;

struct section {
    unsigned int low;
    unsigned int high;
    section (std::string& line) {
        size_t pos = line.find('-');
        std::string left = line.substr(0, pos);
        std::string right = line.substr(pos + 1);
        low = std::stoul(left);
        high = std::stoul(right);
    }

};


bool in_range(section left, section right) {
    if (left.low >= right.low && left.high <= right.high) {
        return true;
    }
    if (left.low <= right.low && left.high >= right.high) {
        return true;
    }
    return false;
}

bool not_overlap(section left, section right) {
    return (left.high < right.low || left.low > right.high);
}

int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }

    size_t count = 0;
    size_t overlap_count = 0;
    for (std::string line; getline(input, line);) {
        size_t pos = line.find(',');
        std::string left = line.substr(0, pos);
        std::string right = line.substr(pos + 1);
        section l { left };
        section r { right };
        ::printf("Line: (%u, %u) with (%u, %u)\n", l.low, l.high, r.low, r.high);
        if (in_range(l, r)) {
            count++;
        }
        if (!not_overlap(l, r)) {
            overlap_count++;
        }
    }
    ::printf("Task 1: %zu\n", count);
    ::printf("Task 2: %zu\n", overlap_count);
    return 0;
}
