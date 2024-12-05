/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2024 - Day 5
 *                  --- Day 5: Print Queue ---
 *
 *        Version:  0.1.0
 *        Created:  05.12.2024
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
#include <set>
#include <sstream>
#include <unordered_map>
#include <print>
using std::string;

std::vector<std::string> split(std::string source, char sep) {
    std::vector<std::string> res {};
    std::stringstream stream { source };
    for (std::string part; getline(stream, part, sep);) {
        res.push_back(part);
    }
    return res;
}
std::vector<int> split_numbers(std::string source, char sep) {
    std::vector<int> res {};
    std::stringstream stream { source };
    for (std::string part; getline(stream, part, sep);) {
        res.push_back(std::stoi(part));
    }
    return res;
}

bool valid_update(const std::vector<int>& update, std::vector<std::pair<int, int>>& rules) {
    std::set<int> passed {};
    for (size_t i = 0; i < update.size(); i++) {
        for (auto& r: rules) {
            if (r.first == update[i] && passed.contains(r.second)) {
                return false;
            }
        }
        passed.emplace(update[i]);
    }
    return true;
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
    std::vector<std::pair<int, int>> rules {};
    for (string line; getline(input, line);) {
        if (line.size() > 0) {
            std::stringstream stream { line };
            int left = 0, right = 0;
            char sep;
            stream >> left >> sep >> right;
            rules.emplace_back(left, right);
        } else {
            break;
        }
    }
    std::vector<std::vector<int>> updates {};
    for (string line; getline(input, line);) {
        if (line.size() > 0) {
            updates.push_back(split_numbers(line, ','));
        } else {
            break;
        }
    }
    uint64_t result = 0;
    for (auto& update: updates) {
        if (valid_update(update, rules)) {
            result += update.at(update.size() / 2);
        }
    }
    std::println("Task 1 result: {}", result);
    return 0;
}
