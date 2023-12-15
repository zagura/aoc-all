/*
 * =====================================================================================
 *
 *       Filename:  task2.cpp
 *
 *    Description:  Advent of Code 2023 - Day 15
 *
 *        Version:  0.1.0
 *        Created:  15.12.2023
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <iostream>
#include <string>
#include <fstream>
#include <format>
#include <cstdio>
// #include <sstream>
#include <algorithm>
#include <array>
#include <list>
// #include <vector>
// #include <queue>
// #include <map>
// #include <set>

struct box {
    std::string label;
    int focal;
    explicit box(std::string l, int f) : label(l), focal(f) {}
};

size_t hash_algo(const std::string& data) {
    size_t value = 0;
    for (const auto& c: data) {
        value += static_cast<unsigned int>(c + 0);
        value = value * 17;
        value = value % 0x100;
    }

    return value;
}

void box_remove(std::list<box>& b, const std::string& label) {
    auto lens = std::find_if(b.begin(), b.end(), [&label](auto l) { return l.label == label; });
    if (lens != b.end()) {
        b.erase(lens);
    }
}

void box_place(std::list<box>& b, const std::string& label, int focal) {
    auto lens = std::find_if(b.begin(), b.end(), [&label](auto l) { return l.label == label; });
    if (lens != b.end()) {
        lens->focal = focal;
    } else {
        b.emplace_back(label, focal);
    }
}

size_t get_power(const std::list<box>& b, size_t box_id) {
    size_t power = 0;
    size_t slot = 1;
    box_id++;
    for (const auto& l: b) {
        auto current_power = (box_id * slot * l.focal);
        std::cout << std::format("Box {}: slot {} [{} {}] -> {}\n", box_id, slot, l.label, l.focal,
                                 current_power);
        power += current_power;
        slot++;
    }
    return power;
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
    size_t hash_sum = 0;
    std::array<std::list<box>, 256> boxes {};
    for (std::string line; std::getline(input, line, ',');) {
        if (line.size() > 0) {
            if (line.back() == '\n') {
                line.pop_back();
            }
            size_t hash = hash_algo(line);
            hash_sum += hash;
            // std::cout << std::format("Step {}: {}\n", line, hash);
            if (line.back() == '-') {
                line.pop_back();
                size_t box_id = hash_algo(line);
                box_remove(boxes[box_id], line);
            } else {
                std::string label = line.substr(0, line.find('='));
                size_t box_id = hash_algo(label);
                int focal = std::stoi(line.substr(line.find('=') + 1));
                // std::cout << std::format("Replace: {} as {} (box {}) {}\n", line, label, box_id, focal);
                box_place(boxes[box_id], label, focal);
            }
        }
    }
    size_t box_id = 0;
    size_t focusing_power = 0;
    for (auto& b: boxes) {
        if (b.empty()) {
            box_id++;
            continue;
        }
        std::cout << std::format("Box {}: ", box_id);
        for (auto& l: b) {
            std::cout << std::format("[{} {}] ", l.label, l.focal);
        }
        focusing_power += get_power(b, box_id);
        box_id++;
        std::cout << std::endl;
    }
    ::printf("Task 1 result: %zu\n", hash_sum);
    ::printf("Task 2 result: %zu\n", focusing_power);
    return 0;
}

