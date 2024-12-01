/*
 * =====================================================================================
 *
 *       Filename:  task2.cpp
 *
 *    Description:  Advent of Code 2023 - Day 8
 *                  --- Day 8: Haunted Wasteland ---
 *
 *        Version:  0.1.0
 *        Created:  09.12.2023
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <memory>
#include <sstream>
#include <format>
#include <vector>

struct Node {
    size_t id;
    std::string name;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    explicit Node(const std::string& n) : id(0), name(n), left(nullptr), right(nullptr) {}
};

std::map<std::string, std::shared_ptr<Node>>
get_jumps(std::map<std::string, std::shared_ptr<Node>>& nodes, const std::string& pattern) {
    std::map<std::string, std::shared_ptr<Node>> jumps {};
    for (auto& [name, node]: nodes) {
        jumps[name] = node;
    }

    for (const auto& c: pattern) {
        for (auto& [name, node]: jumps) {
            switch (c) {
            case 'L':
                node = node->left;
                break;
            case 'R':
                node = node->right;
                break;
            }
        }
    }

    return jumps;
}

bool is_prime(size_t num) {
    for (size_t i = 2; i * i <= num; i++) {
        if (i != num && num % i == 0) {
            return false;
        }
    }
    return true;
}

const std::string& next_step(const std::pair<std::string, std::shared_ptr<Node>>& el) {
    return el.second->name;
}

// std::vector<int> get_single_paths()
size_t get_path_len(const std::string& name, const std::map<std::string, std::shared_ptr<Node>>& jumps) {
    size_t len = 1;
    std::string n = name;
    while (jumps.at(n)->name.back() != 'Z') {
        len++;
        n = jumps.at(n)->name;
        std::cout << std::format("{}: {} -> {}\n", len, name, n);
    }
    return len;
}

size_t gcd(size_t left, size_t right) {
    size_t greater = left;
    size_t lower = right;
    if (lower >= greater) {
        std::swap(greater, lower);
    }
    while (greater != lower && greater % lower != 0) {
        size_t tmp = greater % lower;
        greater = lower;
        lower = tmp;
    }
    return lower;

}

size_t lcm(size_t a, size_t b) {
    return (a / gcd(a, b)) * b;
}

size_t count_paths(const std::map<std::string, std::shared_ptr<Node>>& jumps) {
    std::vector<size_t> paths {};
    for (const auto& [name, node]: jumps) {
        if (name.back() == 'A') {
            paths.push_back(get_path_len(name, jumps));
            std::cout << std::format("Start {} - len: {}\n", name, paths.back());
        }
    }
    size_t lcm_value = 1;
    for (const auto& p: paths) {
        lcm_value = lcm(p, lcm_value);
    }
    return lcm_value;
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
    std::string pattern;
    getline(input, pattern);
    std::map<std::string, std::shared_ptr<Node>> nodes;
    for (std::string line; getline(input, line); ) {
        if (line.empty() or line == "\n") {
            continue;
        }
        std::stringstream line_stream { line };
        std::string token;
        std::string name;
        std::string left;
        std::string right;
        line_stream >> name >> token;
        line_stream >> token;
        left = token.substr(1, token.size() - 2);
        line_stream >> token;
        right = token.substr(0, 3);
        std::shared_ptr<Node> node;
        if (nodes.contains(name)) {
            node = nodes.at(name);
        } else {
            node = std::make_shared<Node>(name);
            nodes.emplace(name, node);
        }
        if (!nodes.contains(left)) {
            std::shared_ptr<Node> n_left = std::make_shared<Node>(left);
            nodes.emplace(left, n_left);
        }
        node->left = nodes.at(left);
        if (!nodes.contains(right)) {
            std::shared_ptr<Node> n_right = std::make_shared<Node>(right);
            nodes.emplace(right, n_right);
        }
        node->right = nodes.at(right);
    }
    // for (const auto& [name, node]: nodes) {
    //     std::cout << std::format("Node {} = [{} , {}]\n", name, node->left->name, node->right->name);
    // }
    std::cout << std::format("Node count {} - pattern size {} (prime - {})\n", nodes.size(), pattern.size(),
                             is_prime(pattern.size()));
    size_t step_count = count_paths(get_jumps(nodes, pattern));
    step_count *= pattern.size();
    ::printf("Task 2 result: %zu\n", step_count);
    return 0;
}

