/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2020 - Day 22
 *
 *        Version:  0.1.0
 *        Created:  22.12.2020
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
#include <queue>
#include <vector>
#include <cinttypes>

using std::string;
using std::vector;
using std::array;
using std::map;
using std::stringstream;
using std::queue;

uint64_t get_result(std::queue<int>& q) {
    uint64_t result = 0;
    for(uint64_t mul = q.size(); !q.empty(); --mul) {
        result += (mul * static_cast<uint64_t>(q.front()));
        q.pop();
    }
    return result;
}

uint64_t play_game (std::queue<int> p1, std::queue<int> p2) {
    uint64_t round_no = 0;
    while ((not p1.empty()) and (not p2.empty())) {
        int card1 = p1.front();
        int card2 = p2.front();
        p1.pop();
        p2.pop();
        if (card1 < card2) {
            p2.push(card2);
            p2.push(card1);
        } else if (card1 > card2) {
            p1.push(card1);
            p1.push(card2);
        }
        round_no++;
        printf("Round %" PRIu64 " %d to %d\n", round_no, card1, card2);
        if (round_no % 25 == 0) {
            printf("Round %" PRIu64 " | %zu - %zu\n", round_no, p1.size(), p2.size());
        }
    }
    return get_result(p1) + get_result(p2);
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
    uint64_t result = 0;
    queue<int> p1 {};
    queue<int> p2 {};
    bool first_deck = true;
    for (string line; getline(input, line); ) {
        if (line.empty()) {
            first_deck = not first_deck;
            continue;
        } else if (line.front() == 'P') {
            // Player header
            continue;
        }
        if (first_deck) {
            p1.push(std::stoi(line));
        } else {
            p2.push(std::stoi(line));
        }
    }
    result = play_game(p1, p2);



    ::printf("Task 1 result: %" PRIu64 "\n", result);
    return 0;
}

