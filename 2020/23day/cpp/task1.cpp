/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2020 - Day 23
 *
 *        Version:  0.1.0
 *        Created:  23.12.2020
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
#include <list>
#include <vector>

constexpr size_t kCupsSize = 9;
constexpr int kRoundCount = 100;
using std::string;
using std::vector;
using std::array;
using std::map;
using std::stringstream;
using cups = std::list<int>;

cups::iterator get_next(cups& l, cups::iterator& current) {
    return (std::next(current)  == l.end() ? l.begin() : std::next(current));
}

void next_move(cups& round_cups, cups::iterator& current_iter) {
    int current_cup = *current_iter;
    printf("cups:");
    for (auto cup: round_cups) {
        if (*current_iter == cup) {
            printf(" (%d)", cup);
        } else {
            printf(" %d", cup);
        }
    }
    printf("\npickup: ");
    cups::iterator next = current_iter;
    next = get_next(round_cups, next);
    vector<int> pick_up {};
    for (int i = 0; i < 3; i++) {
        // Wrap around
        if (next == round_cups.end()) {
            next = round_cups.begin();
        }
        pick_up.push_back(*next);
        next = round_cups.erase(next);
        printf("%d, ", pick_up.back());
    }
    int destination = current_cup - 1;
    if (destination == 0) {
        destination = kCupsSize;
    }
    while (std::find(pick_up.begin(), pick_up.end(), destination) != pick_up.end()) {
        destination--;
        if (destination < 1) {
            destination = kCupsSize;
        }
    }
    auto iter = std::find(round_cups.begin(), round_cups.end(), destination);
    iter = get_next(round_cups, iter);
    round_cups.insert(iter, pick_up.begin(), pick_up.end());
    current_iter = std::find(round_cups.begin(), round_cups.end(), current_cup);
    current_iter = get_next(round_cups, current_iter);
    printf("\ndestination: %d\n\n", destination);

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

    string line;
    getline(input, line);
    cups v {};
    for (char c: line) {
        v.push_back(c - '0');
    }
    for (auto s = v.size() + 1; s <= kCupsSize; ++s) {
        v.push_back(s);
    }
    auto iter = v.begin();
    for (size_t round = 0; round < kRoundCount; round++) {
        printf("-- move %zu --\n" , round + 1);
        next_move(v, iter);
    }

    for(auto& cup: v) {
        printf(" %d", cup);
    }
    printf("\n");
    return 0;
}

