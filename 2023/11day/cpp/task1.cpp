/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2023 - Day 11
 *                  --- Day 11: Cosmic Expansion ---
 *
 *        Version:  0.1.1
 *        Created:  11.12.2023
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <iostream>
#include <numeric>
#include <string>
#include <fstream>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <queue>
#include <algorithm>
#include <vector>
#include <format>


using Coords = std::pair<size_t, size_t>;

size_t dist(const Coords p1, const Coords p2) {
    long long int d1 = p1.first - p2.first;
    long long int d2 = p1.second - p2.second;
    return std::abs(d1) + std::abs(d2);
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
    std::vector<std::string> image {};
    std::vector<Coords> galaxies;
    for (std::string line; getline(input, line);) {
        line_no++;
        if (line.empty() || line == "\n") {
            continue;
        }
        if (line.find('#') == std::string::npos) {
            image.push_back(line);
        }
        image.push_back(line);
    }
    // Insert vertical spaces between galaxies
    std::vector<size_t> empty_cols {};
    for (size_t col = 0; col < image.front().size(); col++) {
        if (std::find_if(image.begin(), image.end(), [&col](const auto& s) {
                return (s.at(col) == '#');
            }) == image.end()) {
            empty_cols.push_back(col);
        } else {
            for (size_t row = 0; row < image.size(); row++) {
                if (image[row][col] == '#') {
                    galaxies.emplace_back(row, col + empty_cols.size());
                }
            }
        }
    }
    std::vector<int> distances {};
    std::cout << std::format("Lines {} read {}, empty cols {}\n", image.size(), line_no, empty_cols.size());
    for (size_t g1 = 0; g1 < galaxies.size() - 1; g1++) {
        for (size_t g2 = g1 + 1; g2 < galaxies.size(); g2++) {
            distances.emplace_back(dist(galaxies.at(g1), galaxies.at(g2)));
        }
    }
    size_t result = 0;
    result = std::accumulate(distances.begin(), distances.end(), 0);

    ::printf("Task 1 result: %zu\n", result);
    return 0;
}

