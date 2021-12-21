/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2021 - Day 21
 *
 *        Version:  0.1.0
 *        Created:  21.12.2021
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
#include <cassert>
using std::string;
using std::vector;
using std::array;
using std::map;
using std::stringstream;

int parse_line(std::string& line) {
    std::stringstream line_stream { line };
    std::string token;
    getline(line_stream, token, ':');
    int value = 0;
    line_stream >> value;
    return value;
}

bool roll_dice(int& dice_value, int& position, int& score, int& rolls_count) {
    if (dice_value > 100) {
        dice_value -= 100;
    }
    int tmp_position = (position + (dice_value * 3) + 6) % 10;
    if (tmp_position == 0) {
        tmp_position = 10;
    }
    rolls_count += 3;
    position = tmp_position;
    score += position;
    dice_value += 3;
    printf("Round: %d, %d, %d\n", dice_value, tmp_position, score);
    return score >= 1000;
}

size_t play(int p1_position, int p2_position) {
    int p1_score = 0;
    int p2_score = 0;
    int dice_value = 0;
    int rolls_count = 0;
    while (true) {
        if (roll_dice(dice_value, p1_position, p1_score, rolls_count)) {
            return p2_score * rolls_count;
        }
        if (roll_dice(dice_value, p2_position, p2_score, rolls_count)) {
            return p1_score * rolls_count;
        }
    }
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

    int p1_position = 0;
    int p2_position = 0;
    std::string line;
    getline(input, line);
    p1_position = parse_line(line);
    getline(input, line);
    p2_position = parse_line(line);
    size_t result = play(p1_position, p2_position);

    ::printf("Task 1 result: %zu\n", result);
    return 0;
}

