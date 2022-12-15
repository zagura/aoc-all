/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2018 - Day 17
 *
 *        Version:  0.1.0
 *        Created:  14.12.2022
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

std::vector<std::string> tokenize(std::string& line) {
    std::string s1 = line.substr(0, line.find(' ') - 1);
    std::string s2 = line.substr(line.find(' ') + 1);
    if (s1[0] == 'x') {

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

    std::vector<std::string> lines;
    for (std::string line; getline(input, line); ) {
        if (line.empty()) {
            continue;
        }
        lines.push_back(line);
    }


    ::printf("Task 1 result: %zu\n", part1(polymer));
    return 0;
}

