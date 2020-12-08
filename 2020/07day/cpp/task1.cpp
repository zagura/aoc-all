/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2020 - Day 7
 *
 *        Version:  0.1.0
 *        Created:  07.12.2020
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
#include <queue>

struct Node {
    std::string name;
    std::set <std::string> contained_in;
    std::map <std::string, int> contain;
};


std::string get_next(std::stringstream& line) {
    std::string result {};
    getline(line, result, ' ');
    return result;
}

int process_graph_task1(const std::map<std::string, Node>& graph, const std::string& search) {
    std::map<std::string, bool> is_possible {};
    std::queue<std::string> to_process {};
    is_possible[search] = true;
    to_process.emplace(search);
    try {
        while (not to_process.empty()) {
            std::string current = to_process.front();
            to_process.pop();
            for (const auto& name: graph.at(current).contained_in) {
                if (is_possible[name] == false) {
                    to_process.emplace(name);
                    is_possible[name] = true;
                }
            }
        }
    }  catch (std::out_of_range& out) {
        std::cerr << "Problem: " << out.what() << std::endl;
    }

    return std::count_if(is_possible.begin(), is_possible.end(), [](const auto& el){ return el.second; });

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
    size_t line_no = 0;
    std::map<std::string, Node> graph;
    for (std::string line; getline(input, line); line_no++) {
        std::stringstream line_stream { line };
        std::string bag_type = get_next(line_stream) + ' ' + get_next(line_stream);
        // bag contain
        get_next(line_stream);
        get_next(line_stream);
        if (graph.find(bag_type) == graph.end()) {
            Node n;
            n.name = bag_type;
            graph.emplace(bag_type, n);
        }
        while (true) {
            std::string next_part = get_next(line_stream);
            if ( next_part == "no") {
                break;
                /// There are no bags in the one type
            } else {
                try {
                    int bag_count = std::stoi(next_part);
                    std::string inside_bag = get_next(line_stream) + ' ' + get_next(line_stream);
                    std::string bag = get_next(line_stream);
                    graph.at(bag_type).contain.emplace(inside_bag, bag_count);
                    if (graph.find(inside_bag) == graph.end()) {
                        Node inside;
                        inside.name = inside_bag;
                        graph.emplace(inside_bag, inside);
                    }
                    graph.at(inside_bag).contained_in.emplace(bag_type);
                    if (bag.back() == '.') {
                        break;
                    }
                } catch (std::invalid_argument& inval) {
                    std::cerr << "Invalid argument of stoi for " << next_part
                              << "\tLine " << line_no << std::endl;
                } catch (std::out_of_range& out) {
                    std::cerr << "Out of range for nodes in: " << bag_type
                              << "\tLine " << line_no << std::endl;
                }
            }
        }
    }
    const std::string my_bag { "gold shiny" };
    for (auto e: graph) {
        std::cout << e.first << "-> (" << e.second.contain.size() << ", "
                  << e.second.contained_in.size() << ')' << std::endl;
    }
    int result = process_graph_task1(graph, my_bag);
    ::printf("Task 1 result: %d\n", result);
    return 0;
}

