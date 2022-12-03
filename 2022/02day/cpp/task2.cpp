/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02.12.2022
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cinttypes>
#include <fmt/format.h>
#include <map>

using std::string;

// A, X - Rock
// B, Y - Paper
// C, Z - Scissors

std::map<char, char> win { { 'A', 'Y'}, { 'B', 'Z' }, { 'C', 'X' }};
std::map<char, char> draw { { 'A', 'X'}, { 'B', 'Y' }, { 'C', 'Z' }};
std::map<char, char> loose { { 'A', 'Z'}, { 'B', 'X' }, { 'C', 'Y' }};


int result(char left, char right) {
    int res = 0;
    char choice = 'A';
    switch (right) {
    case 'Z':
        choice = win.at(left);
        res += 6;
        break;
    case 'Y':
        choice = draw.at(left);
        res += 3;
        break;
    case 'X':
        choice = loose.at(left);
        res += 0;
        break;
    }
    switch (choice) {
    case 'Z':
        res += 3;
        break;
    case 'Y':
        res += 2;
        break;
    case 'X':
        res += 1;
        break;
    }

    return res;
}

int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    long int score = 0;
    for (std::string line; getline(input, line);) {
        if (line == "\n" || line.empty()) {
            // Skip empty line
            continue;
        }
        std::stringstream stream { line };
        char shape1, shape2;
        stream >> shape1 >> shape2;
        int res = result(shape1, shape2);
        printf("Result (%c, %c) -> %d/%ld\n", shape1, shape2, res, score);
        score += res;
    }
    ::printf("Task 1 result: %" PRIu64 "\n", score);
    return 0;
}
