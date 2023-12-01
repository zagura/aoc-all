/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2022 - Day 11
 *
 *        Version:  0.1.1
 *        Created:  11.12.2022
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <cstdint>
#include <iostream>
#include <string>
#include <fstream>
#include <functional>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <queue>
#include <algorithm>
#include <vector>

int parse_action(std::string& line) {
    return static_cast<int>(line.back() - '0');
}

int parse_tests(std::string& line) {
    std::string number = line.substr(line.find_last_of(' ') + 1);
    return std::stoi(number);
}

std::list<int> parse_items(std::string& line) {
    std::list<int> items {};
    std::stringstream line_stream { line.substr(line.find_last_of(':') + 1) };

    for (std::string number; getline(line_stream, number, ','); ) {
        items.push_back(std::stoi(number));
    }
    for (auto& i: items) {
        ::printf("%d\t", i);
    }
    return items;
}

std::vector<std::string> tokenize (const std::string& line, const char delim = ' ') {
    std::vector<std::string> out {};
    std::stringstream line_stream { line };
    for (std::string token; getline(line_stream, token, delim); ) {
        out.push_back(token);
    }
    return out;
}

std::function<int(int)> parse_ops(std::string& line) {
    auto tokens = tokenize(line.substr(line.find('=') + 2));
//    ::printf("Tokens: %zu %s %s\n", tokens.size(), tokens.front().c_str(), tokens.back().c_str());
    if (tokens.back() == "old") {
        return [](int a) noexcept { return a * a; };
    } else {
        int number = std::stoi(tokens.back());
        switch (tokens[1][0]) {
            case '+':
                return [number](int a) noexcept { return a + number; };
            case '*':
                return [number](int a) noexcept { return a * number; };
        }
    }
    return [](int a) noexcept { return a; };
}

struct Context {
    std::vector<std::list<int>> items;
    std::vector<std::function<int (int)>> ops;
    std::vector<int> tests;
    std::vector<std::pair<int, int>> actions;
    std::vector<int> inspections;
};

void round(Context& ctx) {
    for (size_t idx = 0; idx < ctx.items.size(); idx++) {
        std::list<int> items = ctx.items[idx];
        ctx.items[idx].clear();
        for (auto& item: items) {
            ctx.inspections[idx]++;
            int result = ctx.ops[idx](item);
            result /= 3;
            int target = 0;
            if (result % ctx.tests[idx] == 0) {
                target = ctx.actions[idx].first;
            } else {
                target = ctx.actions[idx].second;
            }
            ctx.items[target].push_back(result);
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

    size_t line_no = 0;
    /* Example input record */
    /**
     * Monkey 0:
         Starting items: 79, 98
         Operation: new = old * 19
         Test: divisible by 23
           If true: throw to monkey 2
           If false: throw to monkey 3
    */
    Context ctx;
    int true_action = 0;
    for (std::string line; getline(input, line);) {
        line_no++;
        if (line.empty()) {
            ::printf("%zu: %zu, %d -> (%d, %d)\n", line_no / 7 - 1, ctx.items.back().size(),
                     ctx.tests.back(), ctx.actions.back().first, ctx.actions.back().second);
            continue;

        }
//        int monkey_id = line_no / 7;
        int option = line_no % 7;
        switch (option) {
        case 1:
            ::printf("Line %s for monkey %zu\n", line.c_str(), line_no / 7);
            break;
        case 2:
            ctx.items.push_back(parse_items(line));
            break;
        case 3:
            ctx.ops.push_back(parse_ops(line));
            break;
        case 4:
            ctx.tests.push_back(parse_tests(line));
            break;
        case 5:
            true_action = parse_action(line);
            break;
        case 6:
            ctx.actions.push_back(std::make_pair(true_action, parse_action(line)));
            break;
        }
    }
    ctx.inspections.resize(ctx.items.size());

    for (size_t it = 0; it < 20; it++) {
        printf("After round %zu\n", it);
        round(ctx);
    }
    for (auto& i: ctx.inspections) {
        ::printf("Inspections: %d\n", i);
    }
    std::vector<int> inspections = ctx.inspections;
    std::sort(inspections.begin(), inspections.end());
    size_t result = inspections.back() * inspections[inspections.size() - 2];
    ::printf("Task 1 result: %zu\n", result);
    return 0;
}

