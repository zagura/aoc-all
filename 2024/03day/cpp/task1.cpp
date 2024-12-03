/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Day 3 Advent of Code 2024
 *
 *        Version:  0.1.0
 *        Created:  03.12.2024
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <charconv>
#include <cinttypes>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <format>
#include <print>
#include <regex>

using std::string;
using std::vector;

size_t execute(std::string instr) {
    auto part1 = instr.substr(4);
    auto delim = part1.find_first_of(',');
    auto part2 = part1.substr(delim + 1);
    part1 = part1.substr(0, delim);
    part2 = part2.substr(0, part2.size() - 1);
    auto d1 = std::stoi(part1);
    auto d2 = std::stoi(part2);
    std::println("{} as {} * {} = {}", instr, part1, part2, d1 * d2);
    return d1 * d2;
}


int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    std::vector<std::string> lines {};
    lines.reserve(500);
    std::vector<std::string> matches {};
    std::regex code = std::regex(R"(mul\(\d{1,3},\d{1,3}\))");
    for (std::string line; std::getline(input, line);) {
        if (line == "\n" || line.empty()) {
            // Skip empty line
            continue;
        }
        for(std::smatch sm; std::regex_search(line, sm, code); ) {
            lines.push_back(sm.str());
            std::println("Found: {}", sm.str());
            line = sm.suffix();
        }
    }
    uint64_t task1_result = 0;
    for (auto& l: lines) {
        task1_result += execute(l);
    }
    ::printf("Part 1 result: %" PRIu64 "\n", task1_result);

    return 0;
}
