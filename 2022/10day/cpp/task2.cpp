/*
 * =====================================================================================
 *
 *       Filename:  task2.cpp
 *
 *    Description:  Advent of Code 2022 - Day 10
 *
 *        Version:  0.1.0
 *        Created:  10.12.2022
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <list>
#include <sstream>
#include <vector>

enum class Op {
    noop,
    addx
};

const std::map<Op, int> cycles {
    { Op::noop, 1 },
    { Op::addx, 2}
};

//struct CodeOp {
//    Op instruction;
//    std::vector<int> args;
//};

bool report_cycle(int current_cycle, Op operation) {
    if ((((current_cycle / 20) % 2) == 1) && (current_cycle % 20 == 0)) {
        return true;
    }
    // one cycle before changes everything
    if (operation == Op::addx && (((current_cycle / 20) % 2) == 0) && (current_cycle % 20 == 19)) {
        return true;
    }
    return false;
}

void draw(const std::vector<int>& positions) {
    constexpr int width = 40;
    for (int r = 0; r < 6; r++) {
        std::string line {};
        for (int c = 0; c < width; c++) {
            int middle = positions[r * width + c];
//            printf ("Cycle %d: pos - %d, middle %d\n", r * width + c, c, middle);
            bool lit = (middle == c) || (middle + 1 == c) || (middle - 1 == c);
            line += lit ? '#' : '.';
        }
        printf("row %d: %s\n", r, line.c_str());
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
    std::vector<std::pair<Op, int>> instructions;
    for (std::string line; getline(input, line);) {
        std::string operation;
        int arg;
        Op op;
        std::stringstream line_stream { line };
        line_stream >> operation;
        if (operation == "noop") {
            op = Op::noop;
            instructions.push_back(std::make_pair(op, 0));
        } else if (operation == "addx") {
            line_stream >> arg;
            instructions.push_back(std::make_pair(Op::addx, arg));
        }
    }
    size_t signal_strenght = 0;
    int x = 1;
    size_t cycle_count = 1;
    std::vector<int> positions;
    positions.resize(250);
    for (const auto& i: instructions) {
        if (report_cycle(cycle_count, i.first)) {
            /*
            printf("Cycle %zu: x(%d) - %zu\n", cycle_count, x,
                   x * (cycle_count + (cycle_count % 2)));
            */
            signal_strenght += x * (cycle_count + (cycle_count % 2));
        }
        positions[cycle_count - 1] = x;
        cycle_count += cycles.at(i.first);
        if (i.first == Op::addx) {
            positions[cycle_count - cycles.at(i.first)] = x;
            x += i.second;
        }
//        printf("Cycle %zu: x(%d)\n", cycle_count, x);
    }
    draw(positions);
//    if (report_cycle(cycle_count, Op::noop)) {
//        printf("Cycle %zu: x(%d) - %zu\n", cycle_count, x,
//               x * (cycle_count + (cycle_count % 2)));
//        signal_strenght += x * (cycle_count + (cycle_count % 2));
//    }

    ::printf("Task 1 result: %zu\n", signal_strenght);
    return 0;
}

