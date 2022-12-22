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
#include <memory>
#include <vector>
#include <cassert>
using std::string;
using std::vector;
using std::array;
using std::map;
using std::stringstream;

struct Node {
    std::string key;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    std::shared_ptr<Node> parent;
    char op { '\0' };
    int64_t value { 0 };
    bool ready { false };
    Node(const std::string& monkey, int64_t val) : key(monkey), value(val), ready(true) {}

    Node(const std::string& monkey, std::shared_ptr<Node> par)
        : key(monkey), parent(par), ready(false) {}

    Node(const std::string& monkey, char o) : key(monkey), op(o) {}
};


void solve(std::map<std::string, std::shared_ptr<Node>>& g, const std::string& m) {
    const auto& par = g[m];
    if (par->ready) return;
    if (!par->left->ready) {
        solve(g, par->left->key);
    }
    if (!par->right->ready) {
        solve(g, par->right->key);
    }
    int64_t left = par->left->value;
    int64_t right = par->right->value;
    switch (par->op) {
    case '+':
        par->value = left + right;
        break;
    case '-':
        par->value = left - right;
        break;
    case '*':
        par->value = left * right;
        break;
    case '/':
        par->value = left / right;
        break;
    }
    par->ready = true;
    printf("Ready: %s -> %ld\n", par->key.c_str(), par->value);
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

    std::map<std::string, std::shared_ptr<Node>> data;
    for (std::string line; getline(input, line); ) {
        if (!line.empty()) {
            std::string monkey = line.substr(0, line.find_first_of(':'));
            line = line.substr(line.find_first_of(' ') + 1);
            if (line.find(' ') != std::string::npos) {
                std::string m1 = line.substr(0, line.find(' '));
                std::string m2 = line.substr(line.find_last_of(' ') + 1);
                char o = line[m1.size() + 1];
                if (!data.contains(monkey)) {
                    data[monkey] = std::make_shared<Node>(monkey, o);
                }
                if (!data.contains(m1)) {
                    data[m1] = std::make_shared<Node>(m1, data[monkey]);
                } else {
                    data[m1]->parent = data[monkey];
                }
                if (!data.contains(m2)) {
                    data[m2] = std::make_shared<Node>(m2, data[monkey]);
                } else {
                    data[m2]->parent = data[monkey];
                }
                auto& par = data[monkey];
                par->left = data[m1];
                par->right = data[m2];
                par->op = o;
                par->ready = false;
            } else {
                int64_t number = std::stoi(line);
                if (data.contains(monkey)) {
                    data[monkey]->value = number;
                    data[monkey]->ready = true;
                }
                data[monkey] = std::make_shared<Node>(monkey, number);
            }
        }
    }

    for (auto& [k, m]: data) {
        printf("Monkey: %s\t", k.c_str());
        if (m->parent) {
            printf("Parent: %s\t", m->parent->key.c_str());
        }
        if (m->ready) {
            printf("Value: %ld", m->value);
        }
        if (m->left && m->right) {
            printf("(%s,%c,%s)", m->left->key.c_str(), m->op,  m->right->key.c_str());
        }
        printf("\n");
    }

    solve(data, "root");
//    for (auto& [k, m]: data) {
//        printf("%s: %d\n", k.c_str(), m->value);
//    }
    printf("Root yells: %ld\n", data["root"]->value);
//    ::printf("Task 1 result: %zu\n", result);
    return 0;
}

