/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02.12.2024
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
#include <format>
#include <print>
#include <map>
std::vector<int> get_numbers(std::string str) {
    std::stringstream sstream { str };
    std::vector<int> res {};
    int val;
    while (sstream >> val) {
        res.push_back(val);
    }
    return res;
}

bool cond(int prev, int curr) {
    return ((curr < prev) ||
        (curr - prev < 1) ||
            (curr - prev > 3));
}

bool is_increasing(const std::vector<int>& report) {
    for (size_t i = 1; i < report.size(); i++) {
        auto prev = report[i - 1];
        auto curr = report[i];
        if (cond(prev, curr)) {
            return false;
        }
    }
    return true;
}

bool is_decreasing(const std::vector<int>& report) {
    for (size_t i = 1; i < report.size(); i++) {
        auto prev = report[i - 1];
        auto curr = report[i];
        if (cond(curr, prev)) {
            return false;
        }
    }
    return true;
}

bool is_report_safe(const std::vector<int>& report) {
    return is_decreasing(report) || is_increasing(report);
}

int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    long int score = 0;
    int safe_count = 0;
    for (std::string line; std::getline(input, line);) {
        if (line == "\n" || line.empty()) {
            // Skip empty line
            continue;
        }
        auto report = get_numbers(line);
        if (is_report_safe(report)) {
            safe_count++;
        }
    }
    std::println("Task 1 result {}", safe_count);

    return 0;
}
