/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  AoC 2025 - Day 10
 *
 *        Version:  1.0
 *        Created:  31.12.2025
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */


#include <iostream>
#include <fstream>
#include <list>
#include <sstream>
#include <string_view>
#include <vector>
#include <cinttypes>
#include <print>
#include <format>
#include <map>

using std::vector;
using std::list;
using std::string;
using std::stringstream;

list<string> split(string whole, char sep) {
    list<string> tokens {};
    stringstream sstream { whole };
    for (string token; getline(sstream, token, sep);) {
        tokens.push_back(token);
    }
    return tokens;
}

uint64_t parse_lights(const string& str) {
    uint64_t lights = 0;
    for (size_t i = 0; i < str.size(); i++) {
        if (str[i] == '#') {
            lights += (1 << i);
        }
    }
    return lights;
}

uint64_t try_toggle(uint64_t lights, uint64_t input, const std::vector<uint64_t>& toggles, size_t index, size_t count) {
    if (index == toggles.size()) {
        if (lights == input) return count;
        return 2<<30;
    }
    return std::min(try_toggle(lights, input ^ toggles[index], toggles, index + 1, count + 1),
                    try_toggle(lights, input, toggles, index + 1, count));
}


int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    std::vector<std::string> values {};
    size_t len = 0;
    uint64_t total = 0;
    for (std::string line; getline(input, line);) {
        if (line.empty()) {
            continue;
        }
        list<string> words = split(line, ' ');
        if (words.size() < 2) {
            std::println("Invalid line: {}", line);
        }
        auto lights_str = words.front().substr(1, words.front().size() - 2);
        auto lights = parse_lights(lights_str);
        len = std::max(len, lights_str.size());
        words.pop_front();
        auto joltage = words.back();
        words.pop_back();
        vector<uint64_t> toggles;
        for (auto& w: words) {
            uint64_t toggle {};
            for (auto& n: split(w.substr(1, w.size() - 2), ',')) {
                auto a = std::stoi(n);
                toggle += 1<<a;
            }
            toggles.push_back(toggle);
        }
        auto count = try_toggle(lights, 0, toggles, 0, 0);
        total += count;
        std::println("Joltage: [{}], count: {}", joltage.substr(1, joltage.size() - 2), count);
    }
    std::println("Widest lights: {}", len);
    // for (auto& n: values) {
    //     total += n.size();
    // }
    ::printf("Task 1 result: %" PRIu64 "\n", total);
    return 0;
}
