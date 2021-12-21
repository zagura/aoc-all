/*
 * =====================================================================================
 *
 *       Filename:  task2.cpp
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

enum class Player: bool {
    P1 = true,
    P2 = false,
};
// sum -> result count
// i.e. sum 3 is possible in only one combination 1,1,1
// sum 4 -> 3 different outcomes
static const std::array<std::pair<int, int>, 7> tmp_results = {{
    { 3, 1 },
    { 4, 3 },
    { 5, 6 },
    { 6, 7 },
    { 7, 6 },
    { 8, 3 },
    { 9, 1 }
}};

int parse_line(std::string& line) {
    std::stringstream line_stream { line };
    std::string token;
    getline(line_stream, token, ':');
    int value = 0;
    line_stream >> value;
    return value;
}
constexpr int winning_score = 21;
std::pair<size_t, size_t> roll_dice(int p1_pos, int p2_pos, int p1_score, int p2_score, Player player) {
    if (p1_score >= winning_score) {
        return std::make_pair(1, 0);
    } else if (p2_score >= winning_score) {
        return std::make_pair(0, 1);
    }
    std::pair<size_t, size_t> results = std::make_pair(0, 0);
    for (const auto& [score, count]: tmp_results) {
        std::pair<size_t, size_t> partial {};
        if (player == Player::P1) {
            int pos = (p1_pos + score) % 10;
            if (pos == 0) {
                pos = 10;
            }
            partial = roll_dice(pos, p2_pos, p1_score + pos, p2_score, Player::P2);
        } else {
            int pos = (p2_pos + score) % 10;
            if (pos == 0) {
                pos = 10;
            }
            partial = roll_dice(p1_pos, pos, p1_score, p2_score + pos, Player::P1);
        }
        if (partial.first > 0) {
            results.first += partial.first * count;
        }
        if (partial.second > 0) {
            results.second += partial.second * count;
        }
    }
    return results;
}

size_t play(int p1_position, int p2_position) {
    auto [p1_count, p2_count] = roll_dice(p1_position, p2_position, 0, 0, Player::P1);
    printf("%zu vs %zu\n", p1_count, p2_count);
    if (p1_count > p2_count) { return p1_count; }
    if (p2_count > p1_count) { return p2_count; }
    return 0;

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

