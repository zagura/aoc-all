/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2020 - Day 24
 *
 *        Version:  0.1.0
 *        Created:  03.01.2021
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

constexpr size_t kMapSize = 1100;


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
    vector<array<bool, kMapSize>> tiles {};
    tiles.resize(kMapSize);
    size_t column = kMapSize / 2, row = kMapSize / 2;
    size_t min_col = column, min_row = row, max_col = column, max_row = row;
    size_t count = 0;
    for (string line; getline(input, line); ) {
        stringstream line_stream { line };
        count++;
        column = kMapSize / 2;
        row = kMapSize / 2;
        char direction;
        while (line_stream >> direction) {
            if (direction == 's' || direction == 'n') {
                if (direction == 's') {
                    row += 1;
                } else {
                    row -= 1;
                }
                line_stream >> direction;
                if (direction == 'e') {
                    column += 1;
                } else if (direction == 'w') {
                    column -= 1;
                }
            } else {
                if (direction == 'e') {
                    column += 2;
                } else if (direction == 'w') {
                    column -= 2;
                }
            }
            if (row < min_row) {
                min_row = row;
            } else if (row > max_row) {
                max_row = row;
            }
            if (column < min_col) {
                min_col = column;
            } else if (column > max_col) {
                max_col = column;
            }
        }
        printf("%zu: (%zu, %zu): %d -> %d\n", count, row, column,
               tiles[row][column], not tiles[row][column]);
        tiles[row][column] = (not tiles[row][column]);
    }

    for (size_t r = min_row; r <= max_row; r++) {
        for (size_t c = min_col; c <= max_col; c++) {
            result += (tiles[r][c] == true);
        }
    }



/*  while (input >> dat) {
        arr.push_back(data);
    }
*/

    ::printf("Task 1 result: %d\n", result);
    return 0;
}

