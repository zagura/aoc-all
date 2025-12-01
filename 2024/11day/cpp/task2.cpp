/*
 * =====================================================================================
 *
 *       Filename:  task2.cpp
 *
 *    Description:  Advent of Code 2024 - Day 11
 *                  --- Day 11: Plutonian Pebbles ---
 *
 *        Version:  0.1.0
 *        Created:  12.12.2024
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
#include <cmath>
#include <print>
#include <optional>

struct Pass {
    uint64_t val;
    std::optional<uint64_t> single_digit;
    explicit Pass(uint64_t v) noexcept : val(v), single_digit() {}
};

std::set<uint64_t> vals;

void blink(std::list<Pass>& stones, uint64_t round_id) {
    bool all_passed = true;
    bool filled = true;
    for(auto s = stones.begin(); s != stones.end(); s++) {
        all_passed = all_passed && s->single_digit.has_value();
        if (!vals.contains(s->val)) {
            filled = false;
            vals.insert(s->val);
        }

        if (s->val == 0) {
            if (!s->single_digit) {
                s->single_digit = round_id;
            }
            s->val = 1;
        } else {
            std::string rep = std::to_string(s->val);
            if (rep.size() % 2 == 0) {
                uint64_t div = 1;
                for (size_t i = 0; i < rep.size() / 2; i++) {
                    div *= 10;
                }
                Pass s2 (s->val / div);
                if (s2.val < 10) {
                    s2.single_digit = { round_id };
                }
                stones.insert(s, s2);
                s->val %= div;
                if (s->val < 10) {
                    if (!s->single_digit) {
                        s->single_digit = round_id;
                    }
                }
            } else {
                if (s->val < 10) {
                    if (!s->single_digit) {
                        s->single_digit = round_id;
                    }
                }
                s->val *= 2024;
            }
        }
    }
    std::println("Pass {}: size: {}", round_id, vals.size());
    if (filled) {
        std::println("Pass {}: all values in set", round_id);
        for (auto& e: vals) {
            std::println("Value: {}", e);
        }
    }
    // if (all_passed) {
    //     std::println("All values were at least once single digit since pass {}", round_id);
    //     for (auto& d: stones) {
    //         std::print("{}({})  ", d.val, d.single_digit.value());
    //     }
    //     std::print("\n");
    // }
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
    std::list<Pass> stones {};
    std::stringstream ss { line };
    int n;
    while (ss >> n) {
        stones.emplace_back(n);
    }
    vals = std::set<uint64_t>();
    for (int i = 0; i < 17; i++) {
        std::println("Pass {} - {}", i, stones.size());
        blink(stones, i);
        for(auto s: stones) {
            std::print("{} ", s.val);
        }
        std::print("\n");
    }
    // result = std::accumulate(distances.begin(), distances.end(), 0);

    ::printf("Task 1 result: %zu\n", stones.size());
    return 0;
}

