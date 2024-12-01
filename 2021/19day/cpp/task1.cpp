/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2021 - Day 19 "Beacon scanner"
 *
 *        Version:  0.1.0
 *        Created:  19.12.2021
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <iostream>
#include <string>
#include <fstream>
#include <functional>
#include <sstream>
#include <algorithm>
#include <array>
#include <map>
#include <set>
#include <vector>

using std::string;
using std::vector;
using std::array;
using std::map;
using std::stringstream;

size_t diff(int a, int b) {
    return abs(a - b) * abs(a - b);
}

struct Beacon {
    int x;
    int y;
    int z;
    int scanner_id {};
    int line_no {};
    Beacon(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
    explicit Beacon(std::string line, int scanner, int number) {
        std::stringstream line_stream { line };
        std::array<int, 3> results {};
        size_t id = 0;
        for (std::string token; std::getline(line_stream, token, ','); id++) {
            results[id] = std::stoi(token);
        }
        x = results[0];
        y = results[1];
        z = results[2];
        scanner_id = scanner;
        line_no = number;
    }
    size_t dist(const Beacon& other) {
        return diff(other.x, x) + diff(other.y, y) + diff(other.z, z);
    }
    std::string str() const {
        return "("
               + std::to_string(this->x) + ","
               + std::to_string(this->y) + ","
               + std::to_string(this->z) + ")";
    }
    void move_right() {
        int tmp = z;
        z = y;
        y = x;
        x = tmp;
    }
    void mirror_x() {
        x *= (-1);
    }
    void mirror_y() {
        y *= (-1);
    }
    void mirror_z() {
        z *= -1;
    }
    void rotate() {
        auto tmp_x = x;
        x = z;
        z = tmp_x;
    }
    void translate(int mov_x, int mov_y, int mov_z) {
        x += mov_x;
        y += mov_y;
        z += mov_z;
    }
    void translate(const Beacon& p) {
        translate(p.x, p.y, p.z);
    }
};

int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    if (!input.good()) {
        ::fprintf(stderr, "Cannot open input file\n");
        return 2;
    }

    std::vector<std::vector<Beacon>> scanners;
    scanners.reserve(100);
    int scanner_id = -1;
    int line_no = 0;
    std::set<int> points {};
    for (std::string line; std::getline(input, line); ) {
        if (line.empty()) {
            continue;
        }
        if (line.size() >= 17) {
            scanners.push_back(std::vector<Beacon>());
            scanners.back().reserve(50);
            scanner_id++;
            continue;
        }
        scanners.back().emplace_back(line, scanner_id, line_no);
        points.emplace(line_no);
        line_no++;

    }
    std::map<int, std::vector<std::pair<Beacon, Beacon>>> distances;
    std::map<int, std::set<int>> neighbors;
    for (size_t id = 0; id < scanners.size(); id++) {
        auto& s = scanners[id];
        for (size_t first = 0; first < s.size(); first++) {
            for (size_t second = first + 1; second < s.size(); second++) {
                auto dist = s[first].dist(s[second]);
                distances[dist].emplace_back(s[first], s[second]);
                neighbors[s[first].line_no].emplace(dist);
                neighbors[s[second].line_no].emplace(dist);
            }
        }
    }
    for (auto& n1: neighbors) {
        for (auto& n2: neighbors) {
            if (n1.first != n2.first) {
                std::vector<int> intersect {};
                std::set_intersection(n1.second.begin(), n1.second.end(),
                                          n2.second.begin(), n2.second.end(),
                                          std::back_inserter(intersect));
                if (intersect.size() > 1) {
                    if (points.contains(n1.first) && points.contains(n2.first)) {
                        points.erase(points.find(n2.first));
                    }
                }
            }
        }
    }
    std::erase_if(distances, [](auto& d) { return d.second.size() == 1;});
    ::printf("Task 1 result: %zu\n", points.size());
    return 0;
}

