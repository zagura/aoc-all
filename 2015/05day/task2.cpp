/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2015
 *
 *        Version:  1.0
 *        Created:  13.13.2020
 *
 *         Author:  Michał Zagórski (zagura), <mzagorsk@student.agh.edu.pl>
 *   Organization:  AGH University of Science and Technology, Kraków
 *
 * =====================================================================================
 */
#include <array>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <set>

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::getline;
using std::stringstream;


int main(int argc, char* argv[]) {
    std::ifstream input  { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    const std::set<char> vowels { 'a', 'e', 'i', 'o', 'u'};
    std::array<string, 4> forbidden = { "ab", "cd", "pq", "xy"};
    int result = 0;
    for (string line; getline(input, line); ) {
        auto doubles = 0, repeats = 0;
        for (size_t i = 2; i < line.size(); i++) {
            if (line[i] == line[i-2]) {
                repeats++;
            }
        }
        for(size_t i = 0; i < line.size() - 1; i++) {
            auto s1 = line.substr(i, 2);
            auto s2 = line.substr(i + 2).find(s1);
            if (s2 != std::string::npos) {
                doubles++;
            }
        }
        if (doubles > 0 and repeats > 0) {
            result++;
        }
    }
    ::printf("Task 1 result: %d\n", result);
    return 0;
}

