/*
 * =====================================================================================
 *
 *       Filename:  task2.cpp
 *
 *    Description:  Advent of Code 2024 - Day 10
 *                  --- Day 10: Hoof It ---
 *
 *        Version:  0.1.0
 *        Created:  12.12.2024
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <set>
#include <fstream>
#include <list>
#include <map>
#include <format>
#include <vector>
#include <memory>
#include <print>

using Point = std::pair<int, int>;
struct GraphNode {
    Point loc = {0,0};
    char val = '.';
    std::list<Point> neigh;
    GraphNode(Point p, char c, const std::list<Point>& n) :loc(p), val(c), neigh(n) {}
};
using Graph = std::map<Point, std::shared_ptr<GraphNode>>;
using Data = std::vector<std::string>;
bool bounded(const Point& p, const Data& data) {
    return p.first >= 0  && p.first < static_cast<int>(data.size())
    && p.second >= 0  && p.second < static_cast<int>(data.front().size());
}

int get_val(const Data& graph, Point p) {
    char c = graph.at(p.first)[p.second];
    if (c == '.') return -1;
    return graph.at(p.first)[p.second] - '0';
}

size_t walk_dfs(const Data& graph, Point s) {
    size_t peak_count = 0;
    std::set<Point> visited {};
    std::vector<Point> to_visit {};
    to_visit.push_back(s);
    while (!to_visit.empty()) {
        auto current = to_visit.back();
        to_visit.pop_back();
        if (!bounded(current, graph) || get_val(graph, current) == -1) {
            continue;
        }
        int val = get_val(graph, current);
        if (val == 9) {
            peak_count++;
        } else {
            std::array<Point, 4> neighbors = {{ { -1, 0 }, { 0, -1 }, { 0, 1 }, { 1, 0 } }};
            for (auto [dx, dy]: neighbors) {
                Point neigh { current.first + dx, current.second + dy };
                if (bounded(neigh, graph)) {
                    auto neigh_val = get_val(graph, neigh);
                    if (neigh_val - val == 1) {
                        to_visit.push_back(neigh);
                    }
                }
            }
        }
    }
    return peak_count;
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
    for (std::string line; getline(input, line);) {
        if (line.empty() || line == "\n") continue;
        data.push_back(line);
    }
    size_t result = 0;
    for (size_t i = 0; i < data.size(); i++) {
        for (size_t j = 0; j < data.front().size(); j++) {
            if (get_val(data, {i, j}) == 0) {
                size_t current_peaks = walk_dfs(data, {i, j});
                std::println("({}, {}): {}", i, j, current_peaks);
                result += current_peaks;
            }
        }
    }
    ::printf("Task 1 result: %zu\n", result);
    return 0;
}

