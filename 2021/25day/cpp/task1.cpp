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
#include <cinttypes>

using std::string;
using std::vector;
using std::array;
using std::map;
using std::stringstream;

constexpr int subject_number = 7;
constexpr int divider = 20201227;

uint64_t transform(uint64_t loop_size, uint64_t subject) {
    uint64_t rv = 1;
    for (size_t loop = 0; loop < loop_size; loop++) {
        rv = (rv * subject) % divider;
    }
    return rv;
}

uint64_t find_loop(uint64_t public_key) {
    uint64_t rv = 1;
    uint64_t subject = subject_number;
    size_t loop = 0;
    for (; rv != public_key; loop++) {
        rv = (rv * subject) % divider;
    }
    return loop;
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
    uint64_t door_public, card_public;
    input >> door_public >> card_public;
    uint64_t card_loop = 6, door_loop = 6;
    card_loop = find_loop(card_public);
    door_loop = find_loop(door_public);
    printf("Card loop: %" PRIu64 " Door loop: %" PRIu64 "\n", card_loop, door_loop);
    uint64_t card_encryption = transform(card_loop, door_public);
    uint64_t door_encryption = transform(door_loop, card_public);
    printf("Encryption: card (%" PRIu64"), door(%" PRIu64 ")\n", card_encryption, door_encryption);

    ::printf("Task 1 result: %d\n", result);
    return 0;
}

