/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2023 - Day 7
 *
 *        Version:  0.1.0
 *        Created:  06.12.2023
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */

#include <iostream>
#include <string>
#include <fstream>
#include <format>
#include <cinttypes>
#include <vector>
#include <sstream>

std::vector<size_t> split_line(const std::string& data) {
    std::stringstream line { data };
    std::string info;
    line >> info;
    size_t val;
    std::vector<size_t> res;
    while (line >> val) {
        res.push_back(val);
    }
    return res;
}

size_t count_results(size_t time, size_t dist) {
    size_t possible_results = 0;
    for (size_t t = 0; t <= time; t++) {
        size_t speed = t;
        size_t travel = time - t;
        size_t d = travel * speed;
        if (d > dist) {
            possible_results++;
        }
    }
    std::cout << std::format("T {} & d {} => {}\n", time, dist, possible_results);
    return possible_results;
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
    std::vector<size_t> times;
    std::vector<size_t> distances;
    getline(input, line);
    times = split_line(line);
    getline(input, line);
    distances = split_line(line);
    size_t result = 1;
    for (size_t id = 0; id < times.size(); id++) {
        result *= count_results(times[id], distances[id]);
    }

    ::printf("Task 1 result: %" PRIu64 "\n", result);
    return 0;
}

