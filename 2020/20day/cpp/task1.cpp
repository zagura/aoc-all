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

struct tile {
    int id;
    vector<string> data;
    array<string, 4> sides;
};


int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    if (!input.good()) {
        ::fprintf(stderr, "Cannot open input file\n");
        return 2;
    }
    long long int result = 0;
    vector<tile> tiles;
    tile current_tile = {};
    for (string line; getline(input, line); ) {
        if (line.empty()) {
            tiles.push_back(current_tile);
            current_tile = tile {};
        } else if (line.back() == ':') {
//            printf("line: %s\n", line.c_str());
//            printf("line.substr: %s\n", line.substr(5, 4).c_str());
            int id = std::stoi(line.substr(5, 4));
            current_tile.id = id;
        } else {
            current_tile.data.push_back(line);
        }
    }

    for (auto& t: tiles) {
        // up, left, right, down
        t.sides.front() = t.data.front();
        t.sides.back() = t.data.back();
        string left {};
        string right {};
        for (auto s: t.data) {
            left += s.front();
            right += s.back();
        }
        t.sides[1] = left;
        t.sides[2] = right;
        printf("Id: %d\n", t.id);
        printf("%s, %s, %s, %s\n",
               t.sides[0].c_str(), t.sides[1].c_str(),
               t.sides[2].c_str(), t.sides[3].c_str());
    }
    vector<int> unmached {};
    for (auto& t: tiles) {
        std::array<bool, 4> match {};
        for (auto& other: tiles) {
            if (other.id != t.id) {
                for (int i = 0; i < 4; i++) {
                    for(int j = 0; j < 4; j++) {
                        if (other.sides[j] == t.sides[i]) {
                            match[i] = true;
                        }
                        std::string reversed = other.sides[j];
                        std::reverse(reversed.begin(), reversed.end());
                        if (reversed == t.sides[i]) {
                            match[i] = true;
                        }
                    }
                }
            }
        }
        int not_matched = std::count_if(match.begin(), match.end(), [](bool m) { return m; });
        if (not_matched == 2) {
            printf("Not matched for id: %d\n", t.id);
            unmached.push_back(t.id);
        }
    }
    result = 1;
    for (auto& id: unmached) {
        result *= static_cast<long long int>(id);
    }
    ::printf("Task 1 result: %lld\n", result);
    return 0;
}

