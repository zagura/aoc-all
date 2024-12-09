/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2024 - Day 9
 *
 *        Version:  0.1.0
 *        Created:  09.12.2024
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
#include <print>

std::vector<std::optional<int>> unroll_files(std::string& data){
    std::vector<std::optional<int>> fs {};
    bool file = true;
    int file_id = 0;
    for(auto& c: data) {
        int digit = c - '0';
        for (int i = 0; i < digit; i++) {
            if (file) {
                fs.emplace_back(file_id);
            } else {
                fs.emplace_back();
            }
        }
        if (file) {
            file_id++;
        }
        file = not file;
    }
    return fs;
}
void print_fs(const std::vector<std::optional<int>>& fs) {
    for (auto& c: fs) {
        if (c) {
            std::print("{}", c.value());
        } else {
            std::print(".");
        }
    }
    std::print("\n");
}

std::vector<std::optional<int>> compact_fs(std::vector<std::optional<int>> files) {

    for (size_t i = 0; i < files.size(); i++) {
        if (not files[i]) {
            while (not files.back()) {
                files.pop_back();
            }
            if (i < files.size()) {
                files[i] = files.back();
                files.pop_back();
            }
        }
    }
    return files;
}

uint64_t checksum(const std::vector<std::optional<int>>& fs) {
    uint64_t chksum = 0;
    for (size_t i = 0; i < fs.size(); i++) {
        if (fs[i]) {
            uint64_t u_i = static_cast<uint64_t>(i);
            uint64_t u_b = static_cast<uint64_t>(fs[i].value());
            chksum += (u_i * u_b);
        }
    }
    return chksum;
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
    std::string line;
    std::getline(input, line);
    auto fs = unroll_files(line);
    // print_fs(fs);
    auto compacted = compact_fs(fs);
    // print_fs(compacted);
    uint64_t total_sum = checksum(compacted);

    std::println("Task 1 result: {}", total_sum);
    return 0;
}

