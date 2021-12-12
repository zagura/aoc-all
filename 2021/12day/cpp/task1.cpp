/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2021 - Day 12
 *
 *        Version:  0.1.0
 *        Created:  12.12.2021
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <cctype>
#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <queue>
#include <algorithm>

void print_path(const std::list<std::string>& path) {
    for (auto& s: path) {
        if (s != "end") {
            printf("%s,", s.c_str());
        }
    }
    printf("end\n");
}
void walk_graph(const std::multimap<std::string, std::string>& graph, const std::list<std::string>& path, std::list<std::list<std::string>>& global_paths) {
    auto last_used = path.back();
    auto neigh_range = graph.equal_range(last_used);
    for (auto i = neigh_range.first; i != neigh_range.second; i++) {
        if (i->second == "end") {
            auto l2 = path;
            l2.push_back(i->second);
            global_paths.push_back(l2);
            print_path(l2);
        } else if (i->second == "start") {
            continue;
        } else if (islower(static_cast<int>(i->second[0]))) {
            if (std::find(path.begin(), path.end(), i->second) == path.end()) {
                auto l2 = path;
                l2.push_back(i->second);
                walk_graph(graph, l2, global_paths);
            }
        } else {
            auto l2 = path;
            l2.push_back(i->second);
            walk_graph(graph, l2, global_paths);
        }
    }
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
//    size_t path_count = 0;
    std::vector<std::pair<std::string, std::string>> edges {};

    for(std::string line; getline(input, line); ) {
        if (line.size() > 0) {
            size_t sep = line.find('-');
            if (sep != std::string::npos) {
                edges.emplace_back(line.substr(0, sep), line.substr(sep + 1));
            }
        }
    }
    std::multimap<std::string, std::string> graph;
    for (auto& edge: edges) {
        graph.emplace(edge);
        graph.emplace(edge.second, edge.first);
    }
    std::list<std::list<std::string>> global_paths{};
    std::list<std::string> start_path { "start" };
    walk_graph(graph, start_path, global_paths);

    ::printf("Task 1 result: %zu\n", global_paths.size());
    return 0;
}

