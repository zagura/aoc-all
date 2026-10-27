/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  AoC 2015 - Day 9
 *                  --- Day 9: All in a Single Night ---
 *
 *        Version:  1.0
 *        Created:  27.10.2026
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

struct Edge {
    std::pair<std::string, std::string> ends;
    int distance;
};

using Graph = std::map<std::string, std::map<std::string, int>>;

std::string rep(const std::set<std::string>& data) {
    std::string res = "{";
    for (const auto& d: data) {
        res += d;
        res += ", ";
    }
    res[res.size() - 2] = '}';
    return res;
}

int get_shortest_path(const Graph& graph,
                      const std::vector<std::string>& cities,
                      const std::string& last_city,
                      int current_length,
                      std::set<std::string> used_cities) {
    used_cities.insert(last_city);
    if (cities.size() == used_cities.size()) {
        printf("cities (%zu) %s: %d\n", used_cities.size(), rep(used_cities).c_str(), current_length);
        return current_length;
    }
    auto min_length = INT_MAX;
    for (const auto& c: cities) {
        if (not used_cities.contains(c)) {
            auto len = current_length + graph.at(last_city).at(c);
            if (len > min_length) {
                continue;
            }
            len = get_shortest_path(graph, cities, c, len, used_cities);
            if (len < min_length) {
                min_length = len;
            }
        }
    }
    return min_length;
}

int main(int argc, char* argv[]) {
    std::ifstream input  { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    std::vector<Edge> edges;
    std::map<std::string, std::vector<Edge>> exits;
    std::set<std::string> cities {};
    std::map<std::string, std::map<std::string, int>> graph {};
    for (string line; getline(input, line);) {
        if (line.empty()) {
            continue;
        }
        stringstream ss { line };
        std::vector<string> tokens {};

        for (string token; getline(ss, token, ' ');) {
            tokens.push_back(token);
        }
        Edge e;
        e.ends = std::make_pair(tokens[0], tokens[2]);
        e.distance = std::stoi(tokens[4]);
        edges.push_back(e);
        exits[tokens[0]].push_back(e);
        cities.insert(tokens[0]);
        cities.insert(tokens[2]);
        graph[tokens[0]][tokens[2]] = e.distance;
        graph[tokens[2]][tokens[0]] = e.distance;
    }
    std::vector<std::string> vec_cities {};
    for (auto& c: cities) {
        vec_cities.push_back(c);
    }
    int result = INT_MAX;
    for (auto& c: vec_cities) {
        int tmp = get_shortest_path(graph, vec_cities, c, 0, std::set<std::string>());
        if (tmp < result) {
            result = tmp;
        }
    }
    ::printf("Task 1 result: %d\n", result);


    return 0;
}

