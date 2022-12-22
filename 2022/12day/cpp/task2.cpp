/*
 * =====================================================================================
 *
 *       Filename:  task2.cpp
 *
 *    Description:  Advent of Code 2022 - Day 12
 *
 *        Version:  0.1.0
 *        Created:  13.12.2022
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <queue>
#include <algorithm>


using Coords = std::pair<size_t, size_t>;

int walk_bfs(const std::map<Coords, std::vector<Coords>>& graph, Coords s, std::vector<Coords> e) {
    std::map<Coords, size_t> distances;
    std::set<Coords> visited;
    std::queue<std::pair<Coords, size_t>> to_visit;
    to_visit.emplace(s, 0);
    while (!to_visit.empty()) {
        auto current = to_visit.front();
        to_visit.pop();
        if (!visited.contains(current.first)) {
            visited.insert(current.first);
            distances[current.first] = current.second;
            if (std::find(e.begin(), e.end(), current.first) != e.end()) {
                return current.second;
            }
            auto neighs = graph.at(current.first);
            for (const auto& neigh: neighs) {
                to_visit.emplace(neigh, current.second + 1);
            }
        }
    }
    return distances.at(e.front());
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
    std::vector<std::string> lines;
    std::vector<std::vector<int>> field;
    Coords end;
    std::map<Coords, std::vector<Coords>> graph;
    for(std::string line; getline(input, line); ) {
        if (line.size() > 0) {
            lines.push_back(line);
        }
    }
    field.resize(lines.size());
    std::vector<Coords> starts;
    for (size_t row = 0; row < lines.size(); row++) {
        field[row].resize(lines[row].size());
        for(size_t col = 0; col < lines[row].size(); col++) {
            if (lines[row][col] == 'S') {
                lines[row][col] = 'a';
            } else if (lines[row][col] == 'E') {
                end = std::make_pair(row, col);
                lines[row][col] = 'z';
            }
            field[row][col] = int(lines[row][col] - 'a' + 1);
            if (lines[row][col] == 'a') {
                starts.push_back(std::make_pair(row, col));
            }
        }
    }
    for (int row = 0; row < static_cast<int>(field.size()); row++) {
        for (int col = 0; col < static_cast<int>(field.front().size()); col++) {
            Coords cur = std::make_pair(row, col);
            graph[cur];
            for (auto diff: { -1, 1 }) {
                if (col + diff < static_cast<int>(field.front().size()) && col + diff >= 0) {
                    int elevation = (field[row][col + diff] - field[row][col]);
                    if (elevation <= 1) {
                        graph[std::make_pair(row, col + diff)].push_back(cur);
                    }
                }
                if (row + diff < static_cast<int>(field.size()) && row + diff >= 0) {
                    int elevation = (field[row + diff][col] - field[row][col]);
                    if (elevation <= 1) {
                        graph[std::make_pair(row + diff, col)].push_back(cur);
                    }
                }
            }
        }
    }

    size_t len = walk_bfs(graph, end, starts);
    ::printf("Task 2 result: %zu\n", len);
    return 0;
}
