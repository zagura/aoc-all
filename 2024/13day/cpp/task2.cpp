/*
 * =====================================================================================
 *
 *       Filename:  task2.cpp
 *
 *    Description:  Advent of Code 2024 - Day 13
 *
 *        Version:  0.1.0
 *        Created:  15.12.2024
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <optional>
#include <sstream>
#include <format>
#include <print>
const uint64_t base_prize = 10000000000000ll;
std::vector<std::string> split_line(const std::string& data, char sep) {
    std::stringstream line { data };
    std::vector<std::string> res {};
    for(std::string token; std::getline(line, token, sep);) {
        try {
            res.push_back(token);
        } catch (std::exception& e) {
            std::cout << std::format("Failed to parse {}: {}\n", token, e.what());
        }
    }
    return res;
}

using Point = std::pair<uint64_t, uint64_t>;
struct Task {
    std::pair<uint64_t, uint64_t> a_move;
    std::pair<uint64_t, uint64_t> b_move;
    std::pair<uint64_t, uint64_t> prize;

    uint64_t find_path();
    std::optional<uint64_t> move_a(Point s, uint64_t current_cost);
    std::optional<uint64_t> move_b(Point s, uint64_t current_cost);
};

uint64_t Task::find_path() {
    auto val = move_a({0, 0}, 0);
    auto val_b = move_b({0, 0}, 0);
    auto a = val.value_or(prize.first);
    auto b = val_b.value_or(prize.first);
    if (a < b) { return val.value(); }
    else if (b < a) { return val_b.value(); }
    return 0;
}

std::optional<uint64_t> Task::move_a(Point s, uint64_t current_cost) {
    if (s.first > prize.first || s.second > prize.second) {
        return {};
    } else if (s == prize) {
        return { current_cost };
    }
    s.first += a_move.first;
    s.second += a_move.second;
    current_cost += 3;
    auto val_a = move_a(s, current_cost);
    auto val_b = move_b(s, current_cost);
    auto a = val_a.value_or(prize.first);
    auto b = val_b.value_or(prize.first);
    if (a < b) { return val_a; }
    return val_b;
}
std::optional<uint64_t> Task::move_b(Point s, uint64_t current_cost) {
    if (s.first > prize.first || s.second > prize.second) {
        return {};
    } else if (s == prize) {
        return { current_cost };
    }
    s.first += b_move.first;
    s.second += b_move.second;
    current_cost += 1;
    return move_b(s, current_cost);
}

std::pair<uint64_t, uint64_t> get_move(const std::string& token) {
    auto coords = split_line(token, ',');
    uint64_t dx = std::stoi(coords[0].substr(3));
    uint64_t dy = std::stoi(coords[1].substr(3));
    return { dx, dy };
}

std::pair<uint64_t, uint64_t> get_prize(const std::string& token) {
    auto coords = split_line(token, ',');
    uint64_t x = std::stoi(coords[0].substr(3));
    uint64_t y = std::stoi(coords[1].substr(3));
    return { x, y };
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

    uint64_t total_cost = 0;
    Task t {};
    std::vector<Task> tasks;
    for (std::string line; std::getline(input, line);) {
        if (line.empty() || line == "\n") {
            tasks.push_back(t);
            t = Task();
            continue;
        }
        auto data = split_line(line, ':');
        if (data.front() == std::string("Button A")) {
            t.a_move = get_move(data[1]);
            // std::println("A: '{}'", data[1]);
        } else if (data.front() == std::string("Button B")) {
            // std::println("B: '{}'", data[1]);
            t.b_move = get_move(data[1]);
        } else if (data.front() == "Prize") {
            t.prize = get_prize(data[1]);
            t.prize.first += base_prize;
            t.prize.second += base_prize;
        }
    }
    tasks.push_back(t);

    for(auto& task: tasks) {
        uint64_t path_cost = task.find_path();
        std::println("A ({}, {}), B: ({}, {}), Prize ({}, {}) -> {}",
                     task.a_move.first, task.a_move.second,
                     task.b_move.first, task.b_move.second,
                     task.prize.first, task.prize.second, path_cost);
        total_cost += path_cost;
    }
    std::println("Task 1 result: {}", total_cost);
    return 0;
}

