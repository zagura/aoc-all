/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description: Day 3 Advent of Code 2023
 *
 *        Version:  0.1.0
 *        Created:  03.12.2023
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

using std::string;
using std::vector;

struct Symbol {
    char c = '.';
    size_t x = 0;
    size_t y = 0;
    Symbol() = default;
    Symbol(char sym, size_t row, size_t col) noexcept : c(sym), x(row), y(col) {}
};

struct Number {
    int value = 0;
    size_t len = 0;
    size_t x = 0;
    size_t y_start = 0;
    size_t y_end = 0;
    std::vector<Symbol> symbols {};
};

bool is_digit(char c) noexcept {
    return c >= '0' && c <= '9';
}

bool is_symbol(char c) noexcept {
    return ((!is_digit(c)) && (c != '.'));
}
void find_symbols_row(Number& n, const std::string& line, const size_t row) {
    for (size_t y = n.y_start; y <= n.y_end; y++) {
        if (is_symbol(line[y])) {
            n.symbols.emplace_back(line[y], row, y);
        }
    }

}
void find_symbols(Number& n, std::string& line, size_t row) {
    size_t y = n.y_start;
    if (y > 0) {
        if (is_symbol(line[y - 1])) {
            n.symbols.emplace_back(line[y - 1], row, y - 1);
        }
    }
    y = n.y_end;
    if (y < line.size() - 1) {
        if (is_symbol(line[y + 1])) {
            n.symbols.emplace_back(line[y + 1], row, y + 1);
        }
    }
}


int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    std::vector<std::string> lines {};
    lines.reserve(500);
    std::vector<std::vector<Number>> nums {};
    std::vector<std::vector<Symbol>> symbols {};
    nums.reserve(500);
    size_t line_no = 0;
    for (std::string line; getline(input, line);) {
        if (line == "\n" || line.empty()) {
            // Skip empty line
            continue;
        }
        lines.push_back(line);
        nums.emplace_back();
        symbols.emplace_back();
        ::printf("Line %zu: %s\n", line_no, line.c_str());
        for (size_t i = 0; i < line.size(); i++) {
            char c = line[i];
            if (is_digit(c)) {
                size_t j = i;
                std::string num = "";
                while (j < line.size() && is_digit(line[j])) {
                    num += line[j];
                    j++;
                }
                int value = 0;
                auto [ptr,rc] = std::from_chars(&line[i], &line[j], value);
                if (rc !=  std::errc()) {
                    std::cout << std::format("Line {}: Failed to parse number from {}\n", line_no, num);
                    break;
                }
                Number current {};
                current.value = value;
                current.x = line_no;
                current.y_start = i;
                current.y_end = j - 1;
                current.len = num.size();
                nums.back().push_back(current);
                i = j - 1;
            } else {
                Symbol s {};
                s.c = c;
                s.x = line_no;
                s.y = i;
                symbols.back().push_back(s);
            }
        }
        line_no++;
    }
    for (auto& n: nums[0]) {
        find_symbols(n, lines[0], 0);
        find_symbols(n, lines[1], 1);
        find_symbols_row(n, lines[1], 1);
    }
    for (size_t l = 1; l < lines.size() - 1; l++) {
        for (auto& n: nums[l]) {
            // upper line
            find_symbols_row(n, lines[l - 1], l - 1);
            find_symbols(n, lines[l -1], l - 1);
            // same line
            find_symbols(n, lines[l], l);
            // Lower line
            find_symbols(n, lines[l + 1], l + 1);
            find_symbols_row(n, lines[l + 1], l + 1);
        }
    }
    size_t last_index = nums.size() - 1;
    for (auto& n: nums[last_index]) {
        find_symbols_row(n, lines[last_index - 1], last_index - 1);
        find_symbols(n, lines[last_index - 1], last_index - 1);
        find_symbols(n, lines[last_index], last_index);
    }
    // Task 1
    // Find numbers with neighbors - parts
    std::vector<Number> lonely {};
    std::vector<Number> parts {};
    for (const auto& row: nums) {
        for (const auto& n: row) {
            if (n.symbols.empty()) {
                lonely.push_back(n);
            } else {
                parts.push_back(n);
            }
        }
    }
    uint64_t task1_result = 0;
    for (auto &n: parts) {
        task1_result += n.value;
    }
    ::printf("Part 1 result: %" PRIu64 "\n", task1_result);

    return 0;
}
