/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2020 - Day 14
 *
 *        Version:  0.1.0
 *        Created:  14.12.2020
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


constexpr int bitlen = 36;
uint64_t init_and_bitmask() {
    return 0x0fffffffff;
    /*
    int mask = 1;
    for (int i = 0; i < 36; i++) {
        mask << 1;
        mask += 1;
    }
*/
}

uint64_t mask_value(uint64_t or_mask, uint64_t and_mask, uint64_t value) {
    uint64_t result = value & and_mask;
    std::cout << "Result 1: " << result << std::endl;
    result |= or_mask;
    std::cout << "Result 2: " << result << std::endl;
    return result;
}
// and_mask from 0,
void decode_mask(string mask, uint64_t& or_mask, uint64_t& and_mask) {
    and_mask = init_and_bitmask();
    or_mask = 0;
    // from left to right
    size_t shift = bitlen - 1;
    for (char c: mask) {
        if (c == '1') {
            or_mask |= (1ull << shift);
        } else if (c == '0') {
            and_mask &= (~(1ull << shift));
        }
        shift--;
    }
    std::cout << "Mask: " << mask << std::endl;
    std::cout << "Or:   " << static_cast<std::bitset<bitlen>>(or_mask) << std::endl;
    std::cout << "And:  " << static_cast<std::bitset<bitlen>>(and_mask) << std::endl;
}

uint64_t get_addr(std::string& left) {
    std::string part1 = left.substr(left.find('[') + 1);
    std::cout << "Addr: " << part1.substr(0, part1.size() - 1) << std::endl;
    return std::stoull(part1.substr(0, part1.size() - 1));
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

    uint64_t result = 0;
    uint64_t or_bitmask = 0;
    uint64_t and_bitmask = 0;
    std::map<uint64_t, uint64_t> data;
    for (string line; getline(input, line); ) {
//        std::cout << "Read line: " << line << std::endl;
        if (line.empty()) {
            continue;
        }
        stringstream ss { line };
        std::string left, eq, right;
        ss >> left >> eq;
//        std::cout << "Left: " << left << std::endl;
        if (left == "mask") {
            ss >> right;
            decode_mask(right, or_bitmask, and_bitmask);
        } else {
            uint64_t addr = get_addr(left);
            uint64_t value;
            ss >> value;
//            std::cout << "Value: " << value << std::endl;
//            uint64_t masked_val = mask_value(or_bitmask, and_bitmask, value);
//            std::cout << "Save mem[" << addr
//                      << "] = " << masked_val
//                      << std::endl;
            data[addr] = mask_value(or_bitmask, and_bitmask, value);
        }
    }

    for (const auto& el: data) {
        result += el.second;
    }

    ::printf("Task 1 result: %lu\n", result);
    return 0;
}

