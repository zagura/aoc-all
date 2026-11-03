/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  AoC 2015 - Day 13
 *                  --- Day 13: Knights of the Dinner Table ---
 *
 *        Version:  1.0
 *        Created:  03.11.2026
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
#include <map>
#include <set>
#include <climits>

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::getline;
using std::stringstream;
using Graph = std::map<std::string, std::map<std::string, int>>;

std::string rep(const std::vector<std::string>& data) {
    std::string res = "{";
    for (const auto& d: data) {
        res += d;
        res += ", ";
    }
    res[res.size() - 2] = '}';
    return res;
}

int get_longest_path(const Graph& graph,
                      const std::vector<std::string>& knights,
                      const std::string& first_knight,
                      const std::string& last_knight,
                      int current_length,
                      std::set<std::string> used_knights,
                     std::vector<std::string> path) {
    used_knights.insert(last_knight);
    path.push_back(last_knight);
    if (knights.size() == used_knights.size()) {
        auto len = current_length + graph.at(last_knight).at(first_knight);
        printf("knights (%zu) %s: %d\n", used_knights.size(), rep(path).c_str(), len);
        return len;
    }
    auto max_length = INT_MIN;
    for (const auto& c: knights) {
        if (not used_knights.contains(c)) {
            auto len = current_length + graph.at(last_knight).at(c);
            len = get_longest_path(graph, knights, first_knight, c, len, used_knights, path);
            if (len > max_length) {
                max_length = len;
            }
        }
    }
    return max_length;
}

int main(int argc, char* argv[]) {
    std::ifstream input  { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    Graph graph;
    std::set<std::string> knights;
    for (string line; getline(input, line);) {
        if (line.empty()) {
            continue;
        }
        stringstream ss { line };
        std::vector<string> tokens {};
        for (string token; getline(ss, token, ' ');) {
            tokens.push_back(token);
        }
        if (tokens.size() != 11) {
            printf("Wrong size of line: %s", line.c_str());
        }
        auto k1 = tokens[0];
        auto k2 = tokens.back();
        k2 = k2.substr(0, k2.size() - 1);
        int dist = stoi(tokens[3]);
        if (tokens[2] == "lose") {
            dist *= -1;
        }
        graph[k1][k2] += dist;
        graph[k2][k1] += dist;
        knights.insert(k1);
        knights.insert(k2);
    }
    std::vector<std::string> knights_vec {};
    for (const auto& [k1, v]: graph) {
        for (const auto& [k2, dist]: v) {
            printf("%s <-> %s: %d\n", k1.c_str(), k2.c_str(), dist);
        }
    }
    for (const auto& k: knights) {
        knights_vec.push_back(k);
    }
    int result = get_longest_path(graph, knights_vec, knights_vec[0], knights_vec[0], 0, std::set<std::string>(), std::vector<std::string>());
    ::printf("Task 1 result: %d\n", result);
    return 0;
}

