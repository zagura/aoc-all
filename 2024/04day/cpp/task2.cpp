/*
 * =====================================================================================
 *
 *       Filename:  task2.cpp
 *
 *    Description:  Day 4 Advent of Code 2024
 *
 *        Version:  0.1.0
 *        Created:  04.12.2024
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <algorithm>
#include <iostream>
#include <format>
#include <vector>
#include <string>
#include <fstream>
#include <print>

using std::string;
using std::vector;

std::string word = "MAS";
std::string word_reverse = "SAM";

size_t search_words(std::vector<std::string>& puzzle, size_t row, size_t col) {
    size_t count = 0;
    if (puzzle[row][col] != 'M' && puzzle[row][col] != 'S') {
        return count;
    }
    // down-right, up-left
    if (row + word.size() <= puzzle.size() && col + word.size() <= puzzle[row].size()) {
        std::string temp1 {};
        std::string temp2 {};
        for (size_t i = 0; i < word.size(); i++) {
            temp1 += puzzle[row + i][col + i];
            temp2 += puzzle[row + word.size() - 1 - i][col + i];
        }
        if ((temp1 == word || temp1 == word_reverse) &&
            (temp2 == word || temp2 == word_reverse)) {
            count += 1;
        }

    }
    return count;
}


size_t find_words(std::vector<std::string>& puzzle) {
    size_t word_count = 0;
    for (size_t row = 0; row < puzzle.size(); row++) {
        for (size_t col = 0; col < puzzle[row].size(); col++) {
            size_t count = search_words(puzzle, row, col);
            if (count > 0) {
                std::println("({},{}) -> {}", row, col, count);
            }
            word_count += count;
        }
    }
    return word_count;
}


int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }

    std::vector<std::string> puzzle {};
    for (std::string line; getline(input, line);) {
        if (line.empty() || line == "\n") {
            // Skip empty line
            continue;
        }
        puzzle.push_back(line);
    }
    size_t count = find_words(puzzle);
    ::printf("Task 1: %zu\n", count);
    // ::printf("Task 2: %zu\n", overlap_count);
    return 0;
}
