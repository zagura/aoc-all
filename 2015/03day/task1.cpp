/*
 * =====================================================================================
 *
 *       Filename:  template.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  08.12.2019 12:44:10
 *
 *         Author:  Michał Zagórski (zagura), <mzagorsk@student.agh.edu.pl>
 *   Organization:  AGH University of Science and Technology, Kraków
 *
 * =====================================================================================
 */
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <map>

using std::string;
using std::endl;

int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }

    int x = 0, y = 0;
    char direction = ' ';
    std::map <std::pair<int, int>, int>   visited {};
    visited[std::make_pair(0, 0)] = 1;
    static const std::map<char, std::pair<int, int>> changes = {
        { '^', { 0, 1 }},
        { '<', { -1, 0 }},
        { '>', { 1, 0 }},
        { 'v', { 0, -1 }}
    };

    while (input >> direction) {
        auto change = changes.at(direction);
        x += change.first;
        y += change.second;
        visited[std::make_pair(x,y)]++;
    }
    ::printf("Task 1 result: %zu\n", visited.size());


    return 0;
}

