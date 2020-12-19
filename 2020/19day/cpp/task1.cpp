/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2020 - Day 13
 *
 *        Version:  0.1.0
 *        Created:  13.12.2020
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <array>
#include <map>
#include <vector>

using std::string;
using std::vector;
using std::array;
using std::map;
using std::stringstream;

struct Production {
    int id;
    vector<std::pair<int, int>> prods;
    char terminal = 0;
    bool is_terminal = false;
};

/// Recursively check if word can be produced starting from production i

void print(const Production& p) {
    if (p.is_terminal) {
        printf("%d: '%c'\n", p.id, p.terminal);
        return;
    } else {
        for (const auto& prod: p.prods) {
            printf("%d: %d %d\n", p.id, prod.first, prod.second);
        }
    }
}
/// Outside call for each id in productions
/// match(productions, id, 0, word.size(), word);
bool match(const vector<Production>& productions, int id,
           int start, int end, const string& word) {
    if (end - start < 1) {
        // Shouldn't happen
        return false;
    }
    // terminal symbol
    if (end - start == 1) {
        if (productions[id].is_terminal and productions[id].terminal == word.at(start)) return true;
        if (!productions[id].is_terminal) {
            for (auto& p: productions[id].prods) {
                if (p.second == -1) {
                    return (match(productions, p.first, start, end, word));
                }
            }
        }
        return false;
    } else {
        for (auto& p: productions[id].prods) {
            if (p.second != -1) {
                for (int div = start + 1; div < end; div++) {
                    if (match(productions, p.first, start, div, word)
                        and match(productions, p.second, div, end, word)) {
                        return true;
                    }
                }
            } else {
                if (match(productions, p.first, start, end, word)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool parse(string word, const vector<Production>& productions) {
    for (size_t i = 0; i < productions.size(); i++) {
        if (match(productions, i, 0, word.size(), word)) {
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
    if (!input.good()) {
        ::fprintf(stderr, "Cannot open input file\n");
        return 2;
    }
    int result = 0;
    std::vector<Production> productions;
    productions.resize(140);
    // Input's part 1 - language grammar
    for (string line; getline(input, line); ) {
        if (line.empty()) {
            break; // jump to next loop
        }
        stringstream line_stream { line };
        string token;
        line_stream >> token;
        // First token -> id
        token  = token.substr(0, token.size() - 1);
        int id = std::stoi(token);
        // right site of production
        Production p {};
        p.id = id;
        p.is_terminal = false;
        p.terminal = 0;
        while (line_stream >> token) {
            printf("token: %s\n", token.c_str());
            /// Terminal production
            if (token.front() == '"') {
                p.terminal = token[1];
                p.is_terminal = true;
            } else if (token.front() == '|') {
                continue;
            } else {
                int p1, p2;
                p1 = std::stoi(token);
                if (line_stream >> p2) {
                    p.prods.emplace_back(p1, p2);
                }
                else {
                    p.prods.emplace_back(p1, -1);
                }
            }
        }
        productions[id] = p;
    }
    for (auto& p: productions) {
        print(p);
    }


    // Input's part 2 - words
    for (string line; getline(input, line); ) {
        printf("Word: %s\n", line.c_str());
        if (parse(line, productions)) {
            result++;
        }
    }



/*  while (input >> dat) {
        arr.push_back(data);
    }
*/

    ::printf("Task 1 result: %d\n", result);
    return 0;
}

