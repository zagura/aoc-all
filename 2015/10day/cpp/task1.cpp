/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  AoC 2015 - Day 10
 *                  --- Day 10: Elves Look, Elves Say ---
 *
 *        Version:  1.0
 *        Created:  27.10.2026
 *
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <string>
#include <fstream>
#include <array>
#include <map>
#include <set>
#include <climits>

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::getline;
using std::stringstream;

std::string next_gen(const std::string& word) {
    int last_count = 0;
    int last_symbol = '\0';
    std::string new_word = "";
    for (const auto& c: word) {
        // ::printf("Symbol: %c\n", c);
        if (c != last_symbol) {
            if (last_count > 0) {

                new_word += std::to_string(last_count);
                new_word += last_symbol;
            }
            last_symbol = c;
            last_count = 1;
        } else {
            last_count += 1;
        }
    }
    if (last_count > 0) {
        new_word += std::to_string(last_count);
        new_word += last_symbol;
    }
    return new_word;
}

int main(int argc, char* argv[]) {
    std::ifstream input  { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }

    string line;
    getline(input, line);
    string word = line;
    ::printf("Init %s\n", word.c_str());
    for (int i = 0; i < 40; i++) {
        word = next_gen(word);
        ::printf("Iteration %d (%zu): %s\n", i, word.size(), word.c_str());
    }
    int result = word.size();
    ::printf("Task 1 result: %d\n", result);
    return 0;
}

