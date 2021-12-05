/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2021 - Day 5
 *
 *        Version:  0.1.0
 *        Created:  05.12.2021
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <sstream>
#include <unordered_map>
using std::string;

struct Point {
    int x {};
    int y {};
    Point(): x(0), y(0) {}
    Point(int x_, int y_): x(x_), y(y_) {}
    bool operator ==(const Point& other) const {
        return x == other.x && y == other.y;
    }
    bool operator <(const Point other) const {
        return (std::make_pair(x, y) < std::make_pair(other.x, other.y));
    }
};

std::pair<Point, Point> get_vent(const std::string& line) {
    std::stringstream stream { line };
    std::string p1x, p2x, p1y, p2y, sep;
    getline(stream, p1x, ',');
    getline(stream, p1y, ' ');
    getline(stream, sep, ' ');
    getline(stream, p2x, ',');
    getline(stream, p2y);
    Point p1, p2;
    p1.x = std::stoi(p1x);
    p1.y = std::stoi(p1y);
    p2.x = std::stoi(p2x);
    p2.y = std::stoi(p2y);
    printf("Parsed (%d, %d) -> (%d, %d)\n", p1.x, p1.y, p2.x, p2.y);
    return std::make_pair(p1, p2);
}

std::map<Point, int> count_points(std::vector<std::pair<Point, Point>>& vents) {
    std::map<Point, int> counter;
    for (auto& [start, end]: vents) {
        if (start.x != end.x && start.y != end.y) {
            if (start.x <= end.x) {
                if (start.y <= end.y) {
                    for (int x = start.x, y = start.y; y <= end.y && x <= end.x; x++,y++) {
                        counter[Point(x, y)]++;
                        printf("%d, visit (%d, %d)\n", __LINE__, start.x, y);
                    }
                } else {
                    for (int x = start.x, y = start.y; y >= end.y && x <= end.x; x++,y--) {
                        counter[Point(x, y)]++;
                        printf("%d, visit (%d, %d)\n", __LINE__, start.x, y);
                    }
                }
            } else {
                if (start.y <= end.y) {
                    for (int x = start.x, y = start.y; y <= end.y && x >= end.x; x--,y++) {
                        counter[Point(x, y)]++;
                        printf("%d, visit (%d, %d)\n", __LINE__, start.x, y);
                    }
                } else {
                    for (int x = start.x, y = start.y; y >= end.y && x >= end.x; x--,y--) {
                        counter[Point(x, y)]++;
                        printf("%d, visit (%d, %d)\n", __LINE__, start.x, y);
                    }
                }
            }
            continue;
        }
        if (start.x == end.x) {
            if (start.y  <= end.y) {
                for (int y = start.y; y <= end.y; y++) {
                    counter[Point(start.x, y)]++;
                    printf("%d, visit (%d, %d)\n", __LINE__, start.x, y);
                }
            } else {
                for (int y = start.y; y >= end.y; y--) {
                    counter[Point(start.x, y)]++;
                    printf("%d, visit (%d, %d)\n", __LINE__, start.x, y);
                }
            }
        } else {
            if (start.x  <= end.x) {
                for (int x = start.x; x <= end.x; x++) {
                    counter[Point(x, start.y)]++;
                    printf("%d, visit (%d, %d)\n", __LINE__, x, start.y);
                }
            } else {
                for (int x = start.x; x >= end.x; x--) {
                    counter[Point(x, start.y)]++;
                    printf("%d, visit (%d, %d)\n", __LINE__, x, start.y);
                }
            }
        }
    }
    return counter;
}

int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    if (!input.good()) {
        std::cerr << "Cannot open file" << std::endl;
        return 2;
    }
    std::vector<std::pair<Point, Point>> vents;
    vents.reserve(500);
    for (string line; getline(input, line);) {
        if (line.size() > 0) {
            vents.push_back(get_vent(line));
        }
    }
    auto counter = count_points(vents);
    int total = 0;
    for (auto [p, count]: counter) {
//        printf("P(%d, %d) visited: %d\n", p.x, p.y, count);
        if (count > 1) {
            total += 1;
        }
    }
    printf("Task 2 result: %d\n", total);

}
