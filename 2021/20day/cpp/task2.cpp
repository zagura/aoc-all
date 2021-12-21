/*
 * =====================================================================================
 *
 *       Filename:  task2.cpp
 *
 *    Description:  Advent of Code 2021 - Day 20
 *
 *        Version:  0.1.0
 *        Created:  20.12.2021
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <array>
#include <map>
#include <vector>

using std::string;
using std::vector;
using std::array;
using std::map;

// Create with matching indices
// 876
// 543
// 210
const std::array<std::pair<int, int>, 9> neighbors = {{
    { 1, 1 },   // lower-right
    { 1, 0 },   // down
    { 1, -1 },  // lower-left
    { 0, 1 },   // right
    { 0, 0 },   // current
    { 0, -1 },  // left
    { -1, 1 },  // upper-right
    { -1, 0 },  // up
    { -1, -1 }, // upper-left
}};

template <class T>
bool fits(const int& index, const T& vec) {
    return (index >= 0 && index < static_cast<int>(vec.size()));
}
constexpr size_t margin = 3;
std::vector<std::string> enhance(std::vector<std::string>& real_input, const std::string& pattern, bool lighted) {
/*     std::vector<std::string> input {};
    for (size_t x = 0; x < margin; x++) {
        input.emplace_back(real_input.front().size() + 2 * margin, lighted ? '#' : '.');
    }
    for (auto& row: real_input) {
        std::string addition {};
        if (lighted) {
            addition = std::string(margin, '#');
        } else {
            addition = std::string(margin, '.');
        }
        input.emplace_back(addition + row + addition);
    }
    for (size_t x = 0; x < margin; x++) {
        input.emplace_back(input.front().size() + 2 * margin, lighted ? '#' : '.');
    }
    */
    auto& input = real_input;
    std::vector<std::string> output {};
    output.resize(input.size());
    for (size_t x = 0; x < input.size(); x++) {
        output[x].resize(input[x].size());
        for (size_t y = 0; y < input.front().size(); y++) {
            int index = 0;
            for (size_t id = 0; id < neighbors.size(); id++) {
                const auto& [dx, dy] = neighbors.at(id);
                int row = x + dx;
                int column = y + dy;
                if (fits(row, input) && fits(column, input[row])) {
                    index += ((input[row][column] == '#') << id);
                }
            }
            output[x][y] = pattern[index];
        }
    }
    return output;
}

std::vector<std::string> resize_image(std::vector<std::string>& real_input, bool lighted) {
    size_t total_margin = 50 * margin;
    std::vector<std::string> input {};
    for (size_t x = 0; x < total_margin; x++) {
        input.emplace_back(real_input.front().size() + 2 * total_margin, lighted ? '#' : '.');
    }
    for (auto& row: real_input) {
        std::string addition {};
        if (lighted) {
            addition = std::string(total_margin, '#');
        } else {
            addition = std::string(total_margin, '.');
        }
        input.emplace_back(addition + row + addition);
    }
    for (size_t x = 0; x < total_margin; x++) {
       input.emplace_back(input.front().size() + 2 * total_margin, lighted ? '#' : '.');
    }
    return input;
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
    size_t result = 0;
    std::string pattern;
    getline(input, pattern);
    std::vector<std::string> data {};
    for (string line; getline(input, line); ) {
        if (line.empty()) {
            continue;
        } else {
            data.push_back(line);
        }
    }

    data = resize_image(data, false);
    size_t round_count = 50;
    for (size_t iteration = 0; iteration < round_count; iteration++) {
        data = enhance(data, pattern, false); //iteration % 2);
    }
    printf("%s\n", data[margin].c_str());
    for (size_t row = round_count ; row + (round_count) < data.size(); row++) {
        printf("%c", data[row][margin - 1]);
        for (size_t column = round_count; column + (round_count) < data[0].size(); column++) {
            printf("%c", data[row][column]);
            result += (data[row][column] == '#');
        }
        printf("%c", data[row][data[0].size() - round_count]);
        printf("\n");
    }
    printf("%s\n", data[data.size() - margin].c_str());
    ::printf("Task 1 result: %zu\n", result);
    return 0;
}

