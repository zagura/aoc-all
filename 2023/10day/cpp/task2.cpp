/*
 * =====================================================================================
 *
 *       Filename:  task2.cpp
 *
 *    Description:  Advent of Code 2023 - Day 10
 *                  --- Day 10: Pipe Maze ---
 *
 *        Version:  0.1.0
 *        Created:  11.12.2023
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <algorithm>
#include <iostream>
#include <set>
#include <fstream>
#include <list>
#include <map>
#include <format>
#include <vector>
#include <memory>
#include <queue>

using Point = std::pair<size_t, size_t>;
struct GraphNode {
    Point loc = {0,0};
    char val = '.';
    std::list<Point> neigh;
    GraphNode(Point p, char c, const std::list<Point>& n) :loc(p), val(c), neigh(n) {}
};
using Graph = std::map<Point, std::shared_ptr<GraphNode>>;

std::list<Point> get_neighs(const Point& p, char c) {
    std::list<Point> neighs {};
    switch (c) {
    case 'S':
        [[fallthrough]];
    case '.':
        break;
    case '7':
        neighs.emplace_back(p.first, p.second - 1);
        neighs.emplace_back(p.first + 1, p.second);
        break;
    case 'F':
        neighs.emplace_back(p.first, p.second + 1);
        neighs.emplace_back(p.first + 1, p.second);
        break;
    case 'L':
        neighs.emplace_back(p.first - 1, p.second);
        neighs.emplace_back(p.first, p.second + 1);
        break;
    case '|':
        neighs.emplace_back(p.first - 1, p.second);
        neighs.emplace_back(p.first + 1, p.second);
        break;
    case '-':
        neighs.emplace_back(p.first, p.second - 1);
        neighs.emplace_back(p.first, p.second + 1);
        break;
    case 'J':
        neighs.emplace_back(p.first - 1, p.second);
        neighs.emplace_back(p.first, p.second - 1);
        break;
    }
    return neighs;
}

size_t walk_bfs(const Graph& graph, Point s, Graph& main_loop) {
    // std::map<Point, size_t> distances;
    std::set<Point> visited;
    size_t max_distance = 0;
    std::queue<std::pair<Point, size_t>> to_visit;
    to_visit.emplace(s, 0);
    while (!to_visit.empty()) {
        auto current = to_visit.front();
        to_visit.pop();
        if (!visited.contains(current.first)) {
            visited.insert(current.first);
            main_loop[current.first] = graph.at(current.first);
            if (current.second > max_distance) {
                max_distance = current.second;
            }
            // distances[current.first] = current.second;
            auto neighs = graph.at(current.first)->neigh;
            for (const auto& neigh: neighs) {
                to_visit.emplace(neigh, current.second + 1);
            }
        }
    }
    return max_distance;
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
    std::vector<std::string> data {};
    Point start {};
    std::map<Point, std::shared_ptr<GraphNode>> main_loop {};
    std::map<Point, std::shared_ptr<GraphNode>> nodes {};
    for (std::string line; getline(input, line);) {
        if (line.empty() || line == "\n") continue;
        if (data.empty()) {
            data.push_back(std::string(line.size() + 2, '.'));
        }
        line = "." + line + ".";
        if (line.find('S') != std::string::npos) {
            start = { data.size(), line.find('S') };
            std::cout << std::format("Start point ({}, {})\n", start.first, start.second);
        }
        data.push_back(line);
    }
    data.push_back(std::string(data.back().size(), '.'));
    for (size_t i = 1; i < data.size() - 1; i++) {
        for (size_t j = 1; j < data.front().size() - 1; j++) {
            Point p {i, j};
            if (data[i][j] == '.') continue;
            auto node = std::make_shared<GraphNode>(p, data[i][j], get_neighs(p, data[i][j]));
            if (node->neigh.size() != 2) {
                std::cout << std::format("Node ({}, {}) '{}': {}\n", p.first, p.second, node->val, node->neigh.size());
            }
            nodes.emplace(p, node);

        }
    }
    for (int x: {-1, 1}) {
        if (data[start.first + x][start.second] == '.') continue;
        auto node = nodes.at({start.first + x, start.second});
        if (std::find(node->neigh.begin(), node->neigh.end(), start) != node->neigh.end()) {
            nodes.at(start)->neigh.push_back(node->loc);
        }
    }
    for (int y: {-1, 1}) {
        if (data[start.first][start.second + y] == '.') continue;
        auto node = nodes.at({start.first, start.second + y});
        if (std::find(node->neigh.begin(), node->neigh.end(), start) != node->neigh.end()) {
            nodes.at(start)->neigh.push_back(node->loc);
        }
    }
    for(const auto& [loc, node]: nodes) {
        std::cout << std::format("({}, {}): '{}' -> [({}, {}), ({}, {})]\n", loc.first, loc.second,
                                 node->val, node->neigh.front().first, node->neigh.front().second,
                                 node->neigh.back().first, node->neigh.back().second);
    }
    size_t result = walk_bfs(nodes, start, main_loop);
    std::cout << std::format("Change {} -> {}\n", nodes.size(), main_loop.size());
    for (const auto& [loc, node]: nodes) {
        if (!main_loop.contains(loc)) {
            data[loc.first][loc.second] = '.';
        }
    }
    for (const auto& l: data) {
        std::cout << l << std::endl;
    }




    ::printf("Task 1 result: %zu\n", result);
    return 0;
}

