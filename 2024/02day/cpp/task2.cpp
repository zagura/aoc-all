/*
 * =====================================================================================
 *
 *       Filename:  task2.cpp
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
#include <optional>
#include <format>
#include <print>

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
std::optional<int> is_increasing(const std::vector<int>& report) {
    for (size_t i = 1; i < report.size(); i++) {
        auto prev = report[i - 1];
        auto curr = report[i];
        if (cond(prev, curr)) {
            return {i};
        }
    }
    return {};
}

std::optional<int> is_decreasing(const std::vector<int>& report) {
    for (size_t i = 1; i < report.size(); i++) {
        auto prev = report[i - 1];
        auto curr = report[i];
        if (cond(curr, prev)) {
            return {i};
        }
    }
    return {};
}

std::vector<int> skip(const std::vector<int>& old, size_t skip_index) {
    std::vector<int> report {};
    for (size_t i = 0; i < old.size(); i++) {
        if (i != skip_index) {
            report.push_back(old[i]);
        }
    }
    return report;
}

bool is_report_safe(const std::vector<int>& report, bool fault) {
    auto decr = is_decreasing(report);
    auto incr = is_increasing(report);
    if (!decr || !incr) {
        return true;
    } else if (!fault) {
        if (decr.has_value()) {
            std::vector<int> decr_report = skip(report, decr.value());
            if (is_report_safe(decr_report, true)) {
                return true;
            }
            decr_report = skip(report, decr.value() - 1);
            if (is_report_safe(decr_report, true)) {
                return true;
            }
        }
        if (incr.has_value()) {
            std::vector<int> incr_report = skip(report, incr.value());
            if (is_report_safe(incr_report, true)) {
                return true;
            }
            incr_report = skip(report, incr.value() - 1);
            if (is_report_safe(incr_report, true)) {
                return true;
            }
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    int safe_count = 0;
    for (std::string line; std::getline(input, line);) {
        if (line == "\n" || line.empty()) {
            // Skip empty line
            continue;
        }
        auto report = get_numbers(line);
        if (is_report_safe(report, false)) {
            safe_count++;
        }
    }
    std::println("Task 2 result: {}", safe_count);

    return 0;
}
