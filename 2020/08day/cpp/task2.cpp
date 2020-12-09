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

std::pair<bool, int>
program(const std::vector<std::pair<std::string, int>>& code, std::vector<bool> visited,
        size_t index, long long int acc) {
    //std::vector<bool> visited(code.size());
    bool looped = false;
    for (; index < code.size();) {
        if (visited[index]) {
            looped = true;
            break;
        }
        size_t old_index = index;
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
        visited[old_index] = true;
    }
    if (not looped) {
        std::cout << "Result: " << acc;
    }
    return std::pair((not looped), acc);
}

int outer_program(std::vector<std::pair<std::string, int>> code) {
    std::vector<bool> visited (code.size());
    long long int acc = 0;
    for (size_t index = 0; index < code.size();) {
        printf("Index: %zu\n", index);
        if (visited[index]) {
            std::cout << "Looped at " << index << std::endl;
            break;
        }
        size_t old_index = index;
        auto [op, arg] = code[index];
        if (op == "acc") {
            acc += arg;
            index++;
        } else if (op == "jmp") {
            // Change to nop and check result
            code[index].first = "nop";
            auto res = program(code, visited, index, acc);
            if (res.first) {
                return res.second;
            }
            code[index].first = "jmp";
            index += arg;
        } else {
            code[index].first = "jmp";
            auto res = program(code, visited, index, acc);
            if (res.first) {
                return res.second;
            }
            code[index].first = "nop";
            index += 1;
        }
        visited[old_index] = true;
    }
    return -1;
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

    int result = outer_program(code);
    ::printf("Task 2 result: %d\n", result);
    return 0;
}

