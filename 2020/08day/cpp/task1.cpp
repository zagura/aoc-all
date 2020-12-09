/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2020 - Day 8
 *
 *        Version:  0.1.0
 *        Created:  08.12.2020
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
#include <queue>

int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    if (!input.good()) {
        ::fprintf(stderr, "Cannot open input file\n");
        return 2;
    }
    size_t line_no = 0;
    std::vector<std::pair<std::string, int>> code;
    code.reserve(700);
    for (std::string line; getline(input, line); line_no++) {
        std::stringstream line_stream { line };
        std::string instruction;
        int argument;
        line_stream >> instruction >> argument;
        code.emplace_back(instruction, argument);
//        printf("Op %s, arg: %d\n", instruction.c_str(), argument);
    }
    long long int acc = 0;
    std::vector<bool> visited(code.size());
    for (size_t index = 0; index < code.size();) {
        if (visited[index]) {
            break;
        } else {
            std::cout << "\nindex: " << index;
            visited[index] = true;
        }
        auto [op, arg] = code[index];
        if (op == "acc") {
            std::cout << "Acc: " << arg;
            acc += arg;
            index++;
        } else if (op == "jmp") {
            index += arg;
        } else {
            index += 1;
        }
    }
    int result = acc;
    ::printf("Task 1 result: %d\n", result);
    return 0;
}

