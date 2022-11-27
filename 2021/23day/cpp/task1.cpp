/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2021 - Day 23
 *
 *        Version:  0.1.0
 *        Created:  23.12.2021
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
#include <list>
#include <vector>

using std::string;
using std::vector;
using std::array;
using std::map;
using std::stringstream;


int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    if (!input.good()) {
        ::fprintf(stderr, "Cannot open input file\n");
        return 2;
    }

    std::vector<std::string> data {};
    data.reserve(5);
    for(std::string line; getline(input, line); ) {
        data.push_back(line);
    }
    std::vector<std::pair<char, char>> rooms {};
    rooms.resize(4);
    for (size_t i = 0; i < 4; i++) {
        rooms[i].first = data[2][3 + (i * 2)];
        rooms[i].second = data[3][3 + (i * 2)];
    }
    for (const auto& [c1, c2]: rooms) {
        ::printf("Room: (%c, %c)\n", c1, c2);
    }
    return 0;
}

