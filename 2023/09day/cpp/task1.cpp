/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2023 - Day 9
 *
 *        Version:  0.1.0
 *        Created:  09.12.2023
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <array>
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
void print_vec(const std::vector<int>& vec) {
    for (const auto& v: vec) {
        std::cout << v << " ";
    }
}
void print(const std::vector<std::vector<int>>& diffs) {
    for (size_t i = 0; i < diffs.size(); i++) {
        for (size_t j = 0; j < i; j++) {
            std::cout <<  " ";
        }
        print_vec(diffs[i]);
        std::cout << std::endl;
    }
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
    long int total_sum = 0;
    std::vector<int> estimates {};
    estimates.reserve(500);
    for (std::string line; getline(input, line); ) {
        if (line.empty() || line == "\n") continue;

        std::stringstream line_stream { line };
        int val;
        std::vector<int> line_data {};
        line_data.reserve(50);
        while (line_stream >> val) {
            line_data.push_back(val);
        }
        std::vector<std::vector<int>> diffs;
        diffs.push_back(line_data);
        auto& last_diff = line_data;
        bool all_zeros = false;
        while (!all_zeros) {
            std::vector<int> current_diff {};
            all_zeros = true;
            for (size_t i = 1; i < last_diff.size(); i++) {
                int d = last_diff[i] - last_diff[i - 1];
                current_diff.push_back(d);
                all_zeros = all_zeros && (d == 0);
            }
            diffs.push_back(current_diff);
            last_diff = diffs.back();
        }
        long int base = 0;
        for (int j = static_cast<int>(diffs.size() - 1); j >= 0; j--) {
            diffs[j].push_back(diffs[j].back() + base);
            base = diffs[j].back();
        }
        estimates.push_back(diffs[0].back());
        print(diffs);
    }

    for (const auto& e: estimates) {
        total_sum += e;
    }
    std::cout << "\n\n";
    print_vec(estimates);
    std::cout << "\n";
    ::printf("Task 1 result: %ld\n", total_sum);
    return 0;
}

