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
#include <algorithm>
#include <string>
#include <fstream>
#include <array>
#include <chrono>
#include <thread>

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::getline;
using std::stringstream;

struct Point {
    int x;
    int y;
};

Point get_point(stringstream& ss) {
    Point point;
    string s;
    getline(ss, s, ',');
    point.x = std::stoi(s);
    getline(ss, s, ' ');
    point.y = std::stoi(s);
    return point;
}
void print(const std::array<std::array<bool, 1000>, 1000>& lightmap) {
    for (size_t i = 300; i < 800; i++) {
        for (size_t j = 300; j < 800; j++) {
            if (lightmap.at(i).at(j)) {
                ::printf("*");
            }
            else {
                ::printf(" ");
            }
        }
        printf("\n");
    }
}

int main(int argc, char* argv[]) {
    std::ifstream input  { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    std::array<std::array<int, 1000>, 1000> lightmap {};
    for (string line; getline(input, line);) {
//        std::cout << line << std::endl;
        if (line.empty()) {
            continue;
        }
        stringstream ss { line };
        string op;
        getline(ss, op, ' ');
        if (op == "turn") {
            getline(ss, op, ' ');
        }
        Point begin = get_point(ss);
        string trash;
        getline(ss, trash, ' ');
        Point end = get_point(ss);
//        printf("Parsed: %s (%d, %d) -> (%d, %d)\n", op.c_str(),
//               begin.x, begin.y, end.x, end.y);
        for (int x = begin.x; x <= end.x; x++) {
            for (int y = begin.y; y <= end.y; y++) {
                if (op == "toggle") {
                    lightmap[x][y] = lightmap[x][y] + 2;
                } else {
                    lightmap[x][y] = (op == "on") ? lightmap[x][y] + 1
                                                  : lightmap[x][y] - 1;
                    if (lightmap[x][y] < 0) {
                        lightmap[x][y] = 0;
                    }
                }
            }
        }
//        printf("\033[2J\033[1;1H");
//        print(lightmap);
//        using namespace std::chrono_literals;
//        std::this_thread::sleep_for(50ms);
//        getchar();
    }
    int result = 0;
    for (const auto& row: lightmap) {
        for (const auto& el: row) {
            result += el;
        }
    }
    ::printf("Task 1 result: %d\n", result);


    return 0;
}

