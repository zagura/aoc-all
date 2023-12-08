/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2023 - Day 7
 *
 *        Version:  0.1.0
 *        Created:  07.12.2023
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <format>
#include <fstream>
#include <map>
#include <sstream>
#include <vector>

using std::string;
using std::vector;
constexpr size_t task_size = 100000;

int get_strength(const char c) {
    int value = 0;
    if (c >= '2' && c <= '9') {
        return c - '0';
    }
    switch (c) {
    case 'A':
        value += 1;
    case 'K':
        value += 1;
    case 'Q':
        value += 1;
    case 'J':
        value += 1;
    case 'T':
        value += 10;
    }
    return value;
}
/**  Types:
 *
 * 7 Five of a kind, where all five cards have the same label: AAAAA
 * 6 Four of a kind, where four cards have the same label and one card has a different label: AA8AA
 * 5 Full house, where three cards have the same label, and the remaining two cards share a different label: 23332
 * 4 Three of a kind, where three cards have the same label, and the remaining two cards are each different from any other card in the hand: TTT98
 * 3 Two pair, where two cards share one label, two other cards share a second label, and the remaining card has a third label: 23432
 * 2 One pair, where two cards share one label, and the other three cards have a different label from the pair and each other: A23A4
 * 1 High card, where all cards' labels are distinct: 23456
 */
bool high_card(std::array<int, 5> cards) {
    for (size_t i = 4; i > 0; i--) {
        if (cards[i] - cards[i-1] != 1) {
            return false;
        }
    }
    return true;
}
int get_type(std::string cards) {
    std::array<int, 5> ncards {};

    for (size_t i = 0; i < ncards.size(); i++) {
        ncards[i] = get_strength(cards[i]);
    }
    if (high_card(ncards)) {
        return 1;
    }
    std::map<int, int> counts {};
    for (const auto& c: ncards) {
        counts[c]++;
    }
    std::map<int, int> values {};
    for (auto& [k, v]: counts) {
        values[v]++;
    }
    if (values.contains(5)) {
        return 7;
    } else if (values.contains(4)) {
        return 6;
    } else if (values.contains(3)) {
        if (values.contains(2)) {
            return 5;
        } else return 4;
    } else if (values.contains(2)) {
        if (values[2] == 2) {
            return 3;
        } else if (values[2] == 1) {
            return 2;
        }
    }
    return 0;
}

int get_strength(const std::string& cards) {
    int ret = 0;
    for (const auto& c: cards) {
        ret = (16 * ret) + get_strength(c);
    }
    return ret;
}

struct Deck {
    std::string cards = "";
    int type = 0;
    int strength = 0;
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
    std::vector<std::pair<Deck, unsigned int>> game {};
    for(std::string line; getline(input, line);) {
        if (line.size() == 0 || line == "\n") {
            continue;
        }
        std::stringstream s { line };
        std::string hand;
        unsigned int bid;
        s >> hand >> bid;
        Deck d;
        d.cards = hand;
        d.type = get_type(hand);
        d.strength = get_strength(hand);
        game.emplace_back(d, bid);
    }
    std::sort(game.begin(), game.end(), [](auto p1, auto p2) {
        auto d1 = p1.first;
        auto d2 = p2.first;
        if (d1.type < d2.type) {
            return true;
        } else if (d2.type < d1.type) {
            return false;
        }
        return d1.strength < d2.strength;
    });
    size_t t1 = 0;
    for (size_t i = 0; i < game.size(); i++) {
        auto d = game[i].first;
        std::cout << std::format("Hand {}: type ({}), strength ({:x})\n", d.cards, d.type, d.strength);
        t1 += (i + 1) * game[i].second;
    }

    ::printf("Task 1 result: %zu\n", t1);
    return 0;
}

