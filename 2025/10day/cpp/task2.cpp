/*
 * =====================================================================================
 *
 *       Filename:  task2.cpp
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

#include <bitset>
#include <iostream>
#include <fstream>
#include <list>
#include <sstream>
#include <string_view>
#include <vector>
#include <cinttypes>
#include <print>
#include <thread>
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

vector<int> get_ints(string whole) {
    list<string> tokens = split(whole.substr(1, whole.size() - 2), ',');
    vector<int> numbers {};
    for (const auto& t: tokens) {
        numbers.push_back(std::stoi(t));
    }
    return numbers;
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

string table(const vector<int>& data) {
    std::string res = "[";
    for(const auto& d: data) {
        res += std::format("{}, ", d);
    }
    res += "]";
    return res;
}

vector<int> subtract(vector<int> joltage, const vector<int>& button) {
    for (const auto& b: button) {
        joltage[b]--;
    }
    return joltage;
}

bool check_buttons(const vector<int>& joltage, const vector<vector<int>>& buttons, int count, int& min_count, int min_id, uint64_t& call_count) {
    call_count++;
    if (call_count > 1<<30) {
        return false;
    }
    if (count >= min_count) {
        return true;
    }
    bool all_zeros = true;
    for (const auto& j: joltage) {
        if (j < 0) {
            return false;
        }
        if (j > 0) {
            all_zeros = false;
        }
    }
    if (all_zeros) {
        println("joltage {}, count: {}/{} - iteration: {}", table(joltage), min_count, count, call_count);
        // count should be <= min_count
        min_count = count;
        return true;
    }

    for (int i = min_id; i < static_cast<int>(buttons.size()); i++) {
        if (check_buttons(subtract(joltage, buttons[i]), buttons, count + 1, min_count, i, call_count)) {
            return true;
        }
    }
    return false;
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
        // auto lights = parse_lights(lights_str);
        len = std::max(len, lights_str.size());
        words.pop_front();
        auto joltage = get_ints(words.back());
        words.pop_back();
        vector<vector<int>> buttons;
        for (const auto& w: words) {
            buttons.push_back(get_ints(w));
        }
        std::sort(buttons.begin(), buttons.end(), [](auto& b1, auto& b2) { return b1.size() > b2.size(); });
        int min_count = 1<<30;
        uint64_t call_count = 0;
        if (check_buttons(joltage, buttons, 0, min_count, 0, call_count)) {
            total += min_count;
        }
        std::println("Count: {} after {} iterations", min_count, call_count);
    }
    std::println("Widest lights: {}", len);
    // for (auto& n: values) {
    //     total += n.size();
    // }
    ::printf("Task 1 result: %" PRIu64 "\n", total);
    return 0;
}
