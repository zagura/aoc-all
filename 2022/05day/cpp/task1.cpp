/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2022 - Day 5
 *                  --- Day 5: Supply Stacks ---
 *
 *        Version:  0.1.0
 *        Created:  05.12.2022
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <sstream>
#include <unordered_map>
using std::string;

size_t stack_pos(size_t column) {
    /// Based on string '-1- -2- -3- -4- -5- -6- -7- -8- -9-'
    ///                 '0123456789abcdefghijklmopqrstuvwxyz'
    return (column - 1) * 4 + 1;
}

// std::list<std::string>
void print_cargo(std::map<int, std::vector<char>>& data) {
    size_t columns = data.size();
    size_t height = 0;
    for (const auto& m: data) {
        if (m.second.size() > height) {
            height = m.second.size();
        }
    }
    std::list<std::string> lines {};
    for (size_t s = 0; s < height; s++) {
        std::string stack_line = "";
        for (size_t i = 0; i < stack_pos(columns) + 2; i++) {
            stack_line += ' ';
        }
        for (size_t i = 1; i < columns + 1; i++) {
            if (s >= data[i].size()) {
                continue;
            }
            size_t pos = stack_pos(i);
            if (pos >= stack_line.size()) {
                break;
            }
            stack_line[pos] = data[i][s];
            stack_line[pos - 1] = '[';
            stack_line[pos + 1] = ']';
        }
        lines.push_front(stack_line);
    }
    std::string stack_line = "";
    for (size_t i = 0; i < stack_pos(columns) + 1; i++) {
        stack_line += ' ';
    }
    for (size_t i = 1; i < columns + 2; i++) {
        size_t pos = stack_pos(i);
        if (pos >= stack_line.size()) {
            break;
        }
        stack_line[pos] = static_cast<char>('0' + i);
    }
    lines.push_back(stack_line);
    for (const auto& s: lines) {
        printf("%s\n", s.c_str());
    }
    printf("\n");
}


struct op {
    int count;
    int src;
    int dst;
};

op parse_instruction(std::string& line) {
    std::string ignore;
    std::stringstream line_stream { line };
    op operation {};
    line_stream >> ignore >> operation.count
                >> ignore >> operation.src
                >> ignore >> operation.dst;
    return operation;
}

std::map<int, std::vector<char>> parse_cargo(std::vector<std::string>& lines) {
    lines.pop_back();
    std::map<int, std::vector<char>> stacks {};
    std::reverse(lines.begin(), lines.end());
    for (const auto& line: lines) {
        for (size_t i = 1; i < 10; i++) {
            size_t pos = stack_pos(i);
            if (pos >= line.size()) {
                break;
            }
            char c = line[pos];
            if (c != ' ') {
                stacks[i].push_back(c);
            }
        }
    }
    return  stacks;
}

int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    if (!input.good()) {
        std::cerr << "Cannot open file" << std::endl;
        return 2;
    }
    std::vector<std::string> lines {};
    for (string line; getline(input, line);) {
        if (line.size() > 0) {
            lines.push_back(line);
        } else {
            break;
        }
    }
    std::vector<op> instructions {};
    for (string line; getline(input, line);) {
        if (line.empty()) {
            continue;
        }
        instructions.push_back(parse_instruction(line));
    }
    std::map<int, std::vector<char>> cargo = parse_cargo(lines);
    print_cargo(cargo);
    for (const auto o: instructions) {
        size_t count = o.count;
        while (count) {
            if (cargo[o.src].size() > 0) {
                cargo[o.dst].push_back(cargo[o.src].back());
                cargo[o.src].pop_back();
            }
            count--;
            print_cargo(cargo);
        }
    }
    std::string result {};
    for (const auto& [key, val]: cargo) {
        result += val.back();
    }
    printf("Task 1 result: %s\n", result.c_str());
    return 0;
}
