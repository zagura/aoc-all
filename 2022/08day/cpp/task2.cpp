/*
 * =====================================================================================
 *
 *       Filename:  task2.cpp
 *
 *    Description:  Advent of Code 2022 - Day 8
 *                  --- Day 8: Treetop Tree House ---
 *
 *        Version:  0.1.0
 *        Created:  08.12.2022
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <algorithm>
#include <cinttypes>
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
#include <queue>

constexpr size_t out_len = 4;

int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    if (!input.good()) {
        ::fprintf(stderr, "Cannot open input file\n");
        return 2;
    }
    std::vector<std::vector<uint8_t>> area;
    std::vector<std::vector<bool>> visible;
    std::vector<std::vector<uint32_t>> scores;
    for (std::string line; getline(input, line); ) {
        if (line.empty()) {
            continue;
        }
        area.push_back({});
        visible.push_back({});
        scores.push_back({});
        auto& row = area.back();
        auto& vrow = visible.back();
        auto& srow = scores.back();
        size_t size = line.size();
        row.reserve(size);
        vrow.resize(size);
        srow.resize(size, 1);
        for (const char& c: line) {
            row.push_back(static_cast<uint8_t>(c - '0'));
        }
        uint8_t max_left = row.front(), max_right = row.back();
        vrow.front() = true;
        vrow.back() = true;
        srow.front() = 0;
        srow.back() = 0;
        for (size_t i = 1; i < size - 1; i++) {
            if (row[i] > max_left) {
                vrow[i] = true;
                max_left = row[i];
            }
            if (row[size - 1 - i] > max_right) {
                vrow[size - 1 - i] = true;
                max_right = row[size - 1 - i];
            }
            uint32_t left_score = 0, right_score = 0;
            for (ssize_t l = i - 1; l >= 0; l--) {
                left_score++;
                if (row[l] >= row[i]) {
                    break;
                }
            }
            for (ssize_t r = i + 1; r < size; r++) {
                right_score++;
                if (row[r] >= row[i]) {
                    break;
                }
            }
            srow[i] *= left_score;
            srow[i] *= right_score;
            printf("Row score [%zu][%zu]: %u (%u, %u)\n", scores.size() - 1, i, srow[i], left_score, right_score);

        }
    }
    std::fill(visible.front().begin(), visible.front().end(), true);
    std::fill(visible.back().begin(), visible.back().end(), true);
    std::fill(scores.front().begin(), scores.front().end(), 0);
    std::fill(scores.back().begin(), scores.back().end(), 0);
    for (size_t col = 1; col < area.front().size() - 1; col++) {
        uint8_t max_up = area.front()[col];
        uint8_t max_down = area.back()[col];
        for (size_t row = 1; row < area.size() - 1; row++) {
            if (area[row][col] > max_up) {
                visible[row][col] = true;
                max_up = area[row][col];
            }
            if (area[area.size() - 1 - row][col] > max_down) {
                visible[area.size() - 1 - row][col] = true;
                max_down = area[area.size() - 1 - row][col];
            }
            uint32_t up_score = 0, down_score = 0;
            for (ssize_t u = row - 1; u >= 0; u--) {
                up_score++;
                if (area[u][col] >= area[row][col]) {
                    break;
                }
            }
            for (ssize_t d = row + 1; d < area.size(); d++) {
                down_score++;
                if (area[d][col] >= area[row][col]) {
                    break;
                }
            }
            scores[row][col] *= up_score;
            scores[row][col] *= down_score;
            printf("Score [%zu][%zu]: %u (%u, %u)\n", row, col, scores[row][col], up_score, down_score);
        }
    }

    size_t visible_count = 0;
    for (const auto& r: visible) {
        visible_count += std::count_if(r.begin(), r.end(), [](const auto& d) { return d;});
    }
    uint32_t top_score = 0;
    for (const auto& row: scores) {
        for (const auto& el: row) {
            if (el > top_score) {
                top_score = el;
            }
        }
    }


    ::printf("Task 1 result: %zu\n", visible_count);
    ::printf("Task 2 result: %" PRIu16 "\n", top_score);
    return 0;
}

