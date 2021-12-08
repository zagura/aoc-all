/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2021 - Day 8
 *
 *        Version:  0.1.0
 *        Created:  08.12.2021
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
#include <queue>
#include <list>

constexpr size_t out_len = 4;
/**
 *
 *   dddd
 *  e    a
 *  e    a
 *   ffff
 *  g    b
 *  g    b
 *   cccc
 *
 *   4444
 *  5    1
 *  5    1
 *   6666
 *  7    2
 *  7    2
 *   3333
 *   freqs:
 *   1: 8
 *   2: 9
 *   3: 7
 *   4: 8
 *   5: 6
 *   6: 7
 *   7: 4
 *
 */
static const std::map<int, int> digits {
    {190,  0}, {6, 1}, {218,  2 },  { 94, 3 }, { 102, 4 }, { 124,  5 }, { 252,  6 }, { 22, 7 }, { 254,  8 }, { 126, 9}
};


int decode(const std::vector<std::string>& in, const std::array<std::string, out_len>& out) {
    int out_val = 0;
    std::vector<std::string> data = in;
//    for (auto& el: out) {
//        data.push_back(el);
//    }
    std::map<char, std::list<int>> table{};
    for (auto c: { 'a', 'b', 'c', 'd', 'e', 'f', 'g'}) {
        table[c] = { 1, 2, 3, 4, 5, 6, 7};
    }
    std::map<char, int> counts{};
    for (const auto &el: data) {
        for (auto& c: el) {
            auto& val = table[c];
            counts[c]++;
            if (el.size() == 2) {
                // 1 have only 1 or 2
                val.remove_if([] (int v) {
                    return (v != 1 && v != 2);});
            } else if (el.size() == 3) {
                // 7 is (4, 1, 2)
                val.remove_if([] (int v) {
                    return (v != 1 && v != 2 && v != 4);});
            } else if (el.size() == 4) {
                // 4 is (1,2,5,6)
                val.remove_if([] (int v) {
                    return (v != 1 && v != 2 && v != 5 && v != 6);});
            }
        }
//        if (el.size() == 2) {
//            for (auto entry: table) {
//                if (std::find(el.begin(), el.end(), entry.first) == el.end()) {
//                    table[entry.first].remove_if([] (int v) {
//                        return (v == 1 || v == 2);});
//                }
//            }
//        } else if (el.size() == 3) {
//            for (auto entry: table) {
//                if (std::find(el.begin(), el.end(), entry.first) == el.end()) {
//                    table[entry.first].remove_if([] (int v) {
//                        return (v == 1 || v == 2 || v == 4);});
//                }
//            }
//        }
    }
    std::array<char, 8> known {};
    for (auto& c: counts) {
        if (c.second == 4) {
            (table[c.first]).remove_if([] (int v) { return v != 7; });
            known[7] = c.first;
        } else if (c.second == 9) {
            (table[c.first]).remove_if([] (int v) { return v != 2; });
            known[2] = c.first;
        } else if (c.second == 6) {
            (table[c.first]).remove_if([] (int v) { return v != 5; });
            known[5] = c.first;
        }
        for (auto& c2: table) {
            if (c2.first != c.first) {
                if (c.second == 4) {
                    (table[c2.first]).remove_if([] (int v) { return v == 7; });
                } else if (c.second == 9) {
                    (table[c2.first]).remove_if([] (int v) { return v == 2; });
                } else if (c.second == 6) {
                    (table[c2.first]).remove_if([] (int v) { return v == 5; });
                }
            }
        }
    }

    for (auto entry: table) {
        if (entry.second.size() == 1 && entry.second.front() == 1) {
            known[1] = entry.first;
            for (auto& c2: table) {
                if (c2.first != entry.first) {
                    (table[c2.first]).remove_if([] (int v) { return v == 1; });
                }
            }
        }
    }

    for (auto& entry: table) {
        if (entry.second.size() == 1 && entry.second.front() == 4) {
            known[4] = entry.first;
            for (auto& c2: table) {
                if (c2.first != entry.first) {
                    (table[c2.first]).remove_if([] (int v) { return v == 4; });
                }
            }
        } else if (entry.second.size() == 1 && entry.second.front() == 6) {
            known[6] = entry.first;
            for (auto& c2: table) {
                if (c2.first != entry.first) {
                    (table[c2.first]).remove_if([] (int v) { return v == 6; });
                }
            }
        }
    }

    for (auto& entry: table) {
        if (entry.second.size() == 1 && entry.second.front() == 3) {
            known[3] = entry.first;
            for (auto& c2: table) {
                if (c2.first != entry.first) {
                    (table[c2.first]).remove_if([] (int v) { return v == 3; });
                }
            }
        }
    }
    std::vector<int> outs {};
    for (auto& s: out) {
        int val = 0;
        for (auto c: s) {
            val += (1 << table[c].front());
        }
        outs.push_back(digits.at(val));
    }

    int mul = 1000;
    out_val = 0;
    for (int i = 0; i < 4; i++) {
        out_val += (mul * outs[i]);
        mul /= 10;
    }

    return out_val;
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
    size_t counter = 0;
    std::vector<std::pair<std::vector<std::string>, std::array<std::string, out_len>>> input_data;
    input_data.reserve(2000);
    for (std::string line; getline(input, line); line_no++) {
        std::stringstream line_stream { line };
        std::vector<std::string> left_side {};
        std::array<std::string, out_len> right_side {};
        bool outside = false;
        size_t outside_idx = 0;

        for (std::string token; getline(line_stream, token, ' '); ) {
            if (token == "|") {
                outside = true;
                continue;
            }
            if (outside) {
                right_side[outside_idx] = token;
                outside_idx++;
                if (token.size() < 5 || token.size() > 6) {
                    counter++;
                }
            } else {
                left_side.push_back(token);
            }
        }
        input_data.emplace_back(left_side, right_side);
    }
    size_t total = 0;
    for (auto& [i, o]: input_data) {
        int ret = decode(i, o);
        total += ret;
    }

    ::printf("Task 2 result: %zu\n", total);
    return 0;
}

