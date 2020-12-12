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
        bool nice = false;
        int double_count = 0;
        auto vowel_count = std::count_if(line.begin(), line.end(), [&vowels](char c) { return vowels.contains(c); });
        for (size_t i = 1; i < line.size(); i++) {
            if (line[i] == line[i-1]) {
                double_count++;
            }
        }
        nice = (double_count > 0) and (vowel_count >= 3);
        for (const auto& s: forbidden) {
            if (line.find(s) != std::string::npos) {
                nice = false;
            }
        }
        if (nice) {
            result++;
        }
    }
    ::printf("Task 1 result: %d\n", result);
    return 0;
}

