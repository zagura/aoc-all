/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2020 - Day 23
 *
 *        Version:  0.2.0
 *        Created:  02.01.2021
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
#include <cinttypes>
constexpr int million = 1000 * 1000;
constexpr size_t kCupsSize = million;
constexpr int kRoundCount = 10 * million;
constexpr size_t kPickupSize = 3;
using std::string;
using std::vector;
using std::array;
using std::map;
using std::stringstream;

struct Node {
    int prev;
    int next;
};
using Cups = std::vector<Node>;


void next_move(Cups& cups, int& current) {
//    printf("cups:");
//    for (auto cup: round_cups) {
//        if (*current_iter == cup) {
//            printf(" (%d)", cup);
//        } else {
//            printf(" %d", cup);
//        }
//    }
//    printf("\npickup: ");
    int next = cups[current].next;

    std::array<int, kPickupSize> pick_up;
    pick_up[0] = next;
    for (size_t i = 1; i < kPickupSize; i++) {
        pick_up[i] = cups[pick_up[i-1]].next;
        // Wrap around
//        printf("%d, ", pick_up.back());
    }
    // Skip pick_up part
    cups[current].next = cups[pick_up.back()].next;
    cups[cups[current].next].prev = current;

    int destination = current - 1;
    if (destination == 0) {
        destination = kCupsSize;
    }
    while (std::find(pick_up.begin(), pick_up.end(), destination) != pick_up.end()) {
        destination--;
        if (destination < 1) {
            destination = kCupsSize;
        }
    }
    cups[pick_up.back()].next = cups[destination].next;
    cups[destination].next = pick_up.front();
    cups[pick_up.front()].prev = destination;
    cups[cups[pick_up.back()].next].prev = pick_up.back();
//    current_iter = std::find(round_cups.begin(), round_cups.end(), current_cup);
    current = cups[current].next;
//    printf("\ndestination: %d\n\n", destination);

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
    Cups cups {};
    cups.resize(kCupsSize + 1);
    int last = kCupsSize;
    int start = line.front() - '0';
    for (char c: line) {
        int val = c - '0';
        cups[val].prev = last;
        cups[last].next = val;
        last = val;
    }
    for (auto s = line.size() + 1; s <= kCupsSize; ++s) {
        cups[s].prev = last;
        cups[last].next = s;
        last = s;
    }
    for (size_t round = 0; round < kRoundCount; round++) {
//        printf("-- move %zu --\n" , round + 1);
        next_move(cups, start);
    }

    uint64_t a = cups[1].next;
    uint64_t b = cups[a].next;
    printf("\n");
    printf("Part 2 result: %" PRIu64 "\n", a * b);
    return 0;
}

