/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Day 4 Advent of Code 2020
 *
 *        Version:  0.1.0
 *        Created:  04.12.2021
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <array>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map>

using std::string;
using std::vector;

struct board {
    std::array<std::array<int, 5>, 5> board;
    int board_sum = 0;
    std::array<int, 5> matched_rows {};
    std::array<int, 5> matched_columns {};
    std::vector<int> matched_history;
    int matched_sum = 0;
    int id = 0;
    bool match(int number);
};

board create_board(vector<string> board_text, int id) {
    board b {};
    size_t row_index = 0;
    int board_sum = 0;
    for (auto& row: board_text) {
        std::stringstream record_line { row };
        for (auto& el: b.board[row_index]) {
            record_line >> el;
            board_sum += el;
        }
        row_index++;
    }
    b.id = id;
    b.board_sum = board_sum;
    return b;
}

std::vector<int> read_history(std::string history_str) {
    std::stringstream stream { history_str };
    std::vector<int> history;
    history.reserve(100);
    for (std::string element; getline(stream, element, ','); ) {
        int val = std::stoi(element);
        history.push_back(val);
    }
    return history;
}

bool board::match(int number) {
    size_t s = board.size();
    int count = static_cast<int>(s);
    for (size_t row = 0; row < s; row++) {
        for (size_t column = 0; column < s; column++) {
            if (board[row][column] == number) {
                matched_rows[row]++;
                matched_columns[column]++;
                matched_history.push_back(number);
                matched_sum += number;
                printf("Board %d: %d matched %d: sum %d\n", id, board_sum, number, matched_sum);
                return ((matched_rows[row] == count)
                        || (matched_columns[column] == count));
            }
        }
    }
    return 0;
}

int match_elements(std::vector<board>& boards, int number) {
    for (auto& b: boards) {
        if (b.match(number)) {
            printf("Win board id %d, on number %d with sum %d\n", b.id, number,
                   (b.board_sum - b.matched_sum));
            return number * (b.board_sum - b.matched_sum);
        }
    }
    return 0;
}

int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    std::vector<board> boards;
    boards.reserve(200);
    std::string history_str {};
    getline(input, history_str);
    std::vector<int> history = read_history(history_str);
    getline(input, history_str); // skip empty line
    std::vector<string> current_board {};
    int id = 0;
    for (std::string line; getline(input, line);) {
        ::printf("Line: %zu %zu: %s\n", current_board.size(), line.length(), line.c_str());
        if (current_board.size() == 5) {
            // Skip empty line
            boards.push_back(create_board(current_board, id));
            current_board.clear();
            id++;
            continue;
        } else if (current_board.size() == 0 and line.size() == 0) {
            break;
        }
        current_board.push_back(line);
    }
    if (current_board.size() == 5) {
        boards.push_back(create_board(current_board, id));
    }
    int score = 0;
    for (auto number: history) {
        score = match_elements(boards, number);
        if (score) {
            break;
        }
    }
    ::printf("Total: %zu\n", boards.size());
    ::printf("Task 1: %d\n", score);
    return 0;
}
