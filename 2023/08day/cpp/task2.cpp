/*
 * =====================================================================================
 *
 *       Filename:  task2.cpp
 *
 *    Description:  Advent of Code 2023 - Day 8
 *                  --- Day 8: Haunted Wasteland ---
 *
 *        Version:  0.1.0
 *        Created:  08.12.2023
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
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

bool verify(const std::vector<std::shared_ptr<Node>>& pos) {
    for (const auto& p: pos) {
        if (p) {
            if (p->name.back() != 'Z') {
                return false;
            }
        }
    }
    return true;
}

size_t traverse(std::map<std::string, std::shared_ptr<Node>>& nodes, const std::string& pattern) {
    size_t step_count = 0;
    std::vector<std::shared_ptr<Node>> curr {};
    for (auto& [name, node]: nodes) {
        if (name.back() == 'A') {
            curr.emplace_back(node);
        }
    }
    while (!verify(curr)) {
        for (const auto& c: pattern) {
            if (verify(curr)) break;
            if (step_count % 10000) {
                printf("Steps %zu\n", step_count);
            }
            step_count++;
            for (auto& n: curr) {
                switch (c) {
                case 'L':
                    n = n->left;
                    break;
                case 'R':
                    n = n->right;
                    break;
                }
            }
        }
    }
    return step_count;
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
    for (const auto& [name, node]: nodes) {
        std::cout << std::format("Node {} = [{} , {}]\n", name, node->left->name, node->right->name);
    }
    size_t step_count = traverse(nodes, pattern);

    ::printf("Task 1 result: %zu\n", step_count);
    return 0;
}

