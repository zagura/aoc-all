/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  AoC 2015 - Day 7
 *
 *        Version:  1.0
 *        Created:  25.10.2026
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <string>
#include <fstream>
#include <array>
#include <chrono>
#include <thread>
#include <map>
// #include <print>

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::getline;
using std::stringstream;

class Operation {
public:
    Operation() = default;
    virtual int exec(std::vector<int> args) = 0;
};

class And: public Operation {
public:
    And() = default;
    int exec(std::vector<int> args) override {
        return args[0] & args[1];
    }
};
class Or: public Operation {
public:
    Or() = default;
    int exec(std::vector<int> args) override {
        return args[0] | args[1];
    }
};

class Not: public Operation {
public:
    Not() = default;
    int exec(std::vector<int> args) override {
        return ~args[0];
    }
};


class Lshift: public Operation {
public:
    int val;
    explicit Lshift(int v): val(v) {}
    int exec(std::vector<int> args) override {
        int lshift = args[0] << val;
        return lshift & 0xffff;
    }
};

class Rshift: public Operation {
public:
    int val;
    explicit Rshift(int v): val(v) {}
    int exec(std::vector<int> args) override {
        return args[0] >> val;
    }
};

class Empty: public Operation {
public:
    Empty() = default;
    int exec(std::vector<int> args) override {
        return args[0];
    }
};

struct Node {
    string id;
    int value;
    bool known = false;
    vector<string> outputs;
    std::shared_ptr<Operation> operation;
};

int resolve(std::map<std::string, Node>& wires, const std::string& key) {
    ::printf("[DEBUG] Trying wires for key '%s'\n", key.c_str());
    auto& w = wires.at(key);
    if (w.known) {
        return w.value;
    }
    vector<int> args;
    for (const auto& s: w.outputs) {
        args.push_back(resolve(wires, s));
    }
    int res = w.operation->exec(args);
    w.value = res;
    w.known = true;
    ::printf("Wires['%s'] = %d\n", key.c_str(), res);
    return res;
}

int main(int argc, char* argv[]) {
    std::ifstream input  { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    std::map<std::string, Node> wires {};
    std::array<std::shared_ptr<Operation>, 4> ops { std::shared_ptr<And>(new And()),
                                              std::shared_ptr<Or>(new Or()),
                                              std::shared_ptr<Not>(new Not()),
                                              std::shared_ptr<Empty>(new Empty()),
                                              };
    // Special case for 1 AND x -> y
    Node one;
    one.value = 1;
    one.operation = ops[3];
    one.id = "1";
    one.known = true;
    one.outputs = std::vector<string>();
    wires["1"] = one;
    for (string line; getline(input, line);) {
        //        std::cout << line << std::endl;
        if (line.empty()) {
            continue;
        }
        stringstream ss { line };
        std::vector<string> tokens {};
        for(string token; getline(ss, token, ' ');) {
            tokens.push_back(token);
        }
        printf("Tokens count %zu\n", tokens.size());
        string identifier = tokens.back();
        tokens.pop_back();
        tokens.pop_back();
        Node n;
        n.value = 0;
        n.known = false;
        n.id = identifier;
        n.outputs = std::vector<string>();
        if (tokens.size() == 1) {
            n.operation = ops[3];
            try {
                int value = std::stoi(tokens[0]);
                n.value = value;
                n.known = true;
            } catch (std::invalid_argument& e) {
                n.value = 0;
                n.outputs.push_back(tokens[0]);
            }
        }
        else if (tokens.size() == 2) {
            if (tokens[0] == "NOT") {
                n.value = 0;
                n.operation = ops[2];
                n.known = false;
                n.outputs.push_back(tokens[1]);
            } else {
                std::printf("Error: %s\n", line.c_str());
            }
        } else {
            ::printf("Tokens: %s, %s, %s\n", tokens[0].c_str(), tokens[1].c_str(), tokens[2].c_str());
            n.value = 0;
            n.known = false;
            n.outputs.push_back(tokens[0]);
            if (tokens[1] != "LSHIFT" && tokens[1] != "RSHIFT") {
                n.outputs.push_back(tokens[2]);
                if (tokens[1] == "OR") {
                    n.operation = ops[1];
                } else {
                    n.operation = ops[0];
                }
            } else {
                int v = std::stoi(tokens[2]);
                if (tokens[1] == "LSHIFT") {
                    n.operation = std::shared_ptr<Lshift>(new Lshift(v));
                }
                else {
                    n.operation = std::shared_ptr<Rshift>(new Rshift(v));
                }
            }
        }
        wires[identifier] = n;
    }
    int result = resolve(wires, "a");
    for (auto& [k, n]: wires) {
        printf("w[%s] = %d, (%d)\n", k.c_str(), n.value, n.known);
    }
    ::printf("Task 1 result: %d\n", result);


    return 0;
}

