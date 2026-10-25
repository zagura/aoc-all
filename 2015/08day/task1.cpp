/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  AoC 2015 - Day 8
 *                  --- Day 8: Matchsticks ---
 *
 *        Version:  1.0
 *        Created:  25.10.2026
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
#include <chrono>
#include <thread>
#include <map>

using std::string;
using std::cin;
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
    int diffs = 0;
    for (string line; getline(input, line);) {
        //        std::cout << line << std::endl;
        if (line.empty()) {
            continue;
        }
        stringstream ss { line };
        std::vector<string> tokens {};
        // printf("line (%s): %zu\n", line.c_str(), line.size());
        auto code_len = line.size();
        size_t mem_len = 0;
        std::vector<int> hexes {};
        for (size_t i = 1; i < code_len - 1; ) {
            if (line[i] == '\\') {
                if (line[i + 1] == '\'' or line[i + 1] == '\\' or line[i + 1] == '"') {
                    i++;
                } else if (line[i + 1] == 'x') {
                    try {
                        auto val = std::stoi(std::string() + line[i + 2] + line[i + 3], nullptr, 16);
                        hexes.push_back(val);
                    } catch(std::invalid_argument& err) {
                        printf("Error: %s", err.what());
                        printf("Line: %s -> %c %c\n", line.c_str(), line[i + 2], line[i + 3]);
                    }

                    i += 3;
                }
            }

            mem_len += 1;
            i += 1;
        }
        printf("line (%s): %zu -> %zu\n", line.c_str(), line.size(), mem_len);
        diffs += (code_len - mem_len);
    }

    int result = diffs;
    ::printf("Task 1 result: %d\n", result);


    return 0;
}

