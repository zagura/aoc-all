/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2020 - Day 19
 *
 *        Version:  0.2.0
 *        Created:  19.12.2020
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
/**
 * As I couldn't find simple solution, this program get different input for part 1 and part2,
 * where grammar is presented in Chomsky normal form: https://en.wikipedia.org/wiki/Chomsky_normal_form
 * Changes needed:
 *  * part1: remove production 8 and place 0: 42 11 instead
 *           remove production 121 and append possible outcomes to productions which use 121
 *  * part2: replace 8: 42 into 8: 42 8 | (42 right side)
 *           append new productions 121: 11 31 and 133: 42 11
 *           to replace 11: 42 31 into 11: 42 31 | 42 121 | 133 11
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

// CYK algorithm: https://en.wikipedia.org/wiki/CYK_algorithm
bool parse(string word, const vector<Production>& productions, const vector<int>& terminals) {
    /// Prepare helper table
    vector<vector<vector<int>>> table {};
    table.resize(word.size());
    for (auto& t: table) {
        t.resize(word.size());
    }
    /// Put productions into first row of table
    for (size_t i = 0; i < word.size(); i++) {
        for (auto t: terminals) {
            if (productions[t].terminal == word.at(i)) {
                table[0][i].push_back(t);
            }
        }
    }

    for (size_t i = 1; i < word.size(); i++) { // row
        for (size_t start = 0; start < word.size() - i; start++) {  // column
            /// We are calucalating table[i][start] := table[i-div][start] table
            for (size_t div = 0; div < i; div++) {
                vector<int>& left = table[div][start];
                vector<int>& right = table[i - div - 1][start + div + 1];
//                printf("Check [%zu, %zu] from [%zu][%zu] and [%zu][%zu]\n",
//                       i, start, div, start, i - div - 1, start + div + 1);
                for (const auto& l: left) {
                    for (const auto& r: right) {
                        for (auto& p: productions) {
                            if (std::find(p.prods.begin(), p.prods.end(), std::make_pair(l, r)) != p.prods.end()) {
                                table[i][start].push_back(p.id);
//                                printf("Matched rule %d: for [%zu, %zu]\n", p.id, i, start);
                            }
                        }
                    }
                }
            }
        }
    }
    auto& last = table.back().front();
    return (std::find(last.begin(), last.end(), 0) != last.end());
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
    std::vector<int> terminals;
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
//            printf("token: %s\n", token.c_str());
            /// Terminal production
            if (token.front() == '"') {
                p.terminal = token[1];
                p.is_terminal = true;
                terminals.push_back(id);
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
    /// Normalize two rules that doesn't match

    // Input's part 2 - words
    for (string line; getline(input, line); ) {
        if (parse(line, productions, terminals)) {
            printf("Word: %s\n", line.c_str());
            result++;
        }
    }

    ::printf("Task 1 result: %d\n", result);
    return 0;
}

