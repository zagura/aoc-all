/*
 * =====================================================================================
 *
 *       Filename:  task2.cpp
 *
 *    Description:  Advent of Code 2020 - Day 17
 *
 *        Version:  0.1.0
 *        Created:  17.12.2020
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <array>
#include <map>
#include <vector>
#include <unordered_map>

using std::string;
using std::vector;
using std::array;
using std::map;
using std::pair;
using std::make_pair;
using std::stringstream;
struct Point3D {
    Point3D(int X, int Y, int Z) noexcept: x(X), y(Y), z(Z)  {}
    int x = 0;
    int y = 0;
    int z = 0;
    bool operator==(const Point3D& other) {
        return (other.x == x)
               and (other.y == y)
               and (other.z == z);
    }
};

std::array<int, 3> dim_change = { -1, 0, 1};

vector<Point3D> make_cycle(vector<Point3D>& data) {
    vector<Point3D> new_data {};
    // z -> [(x,y) -> int]
    std::unordered_map<int, map<pair<int, int>, int>> neigh {};
    neigh.reserve(data.size() * 2);
    new_data.reserve(data.size());

    for (const auto& p: data) {
        for (int dx: {-1, 0, 1}) {
            for (int dy: {-1, 0, 1}) {
                for (int dz: {-1, 0, 1}) {
                    // All three values are 0, we are at the same point as p
                    if ((dx | dy | dz) != 0) {
                        neigh[p.z + dz][make_pair(p.x + dx, p.y + dy)]++;
                    }
                }
            }
        }
    }

    for (auto& z: neigh) {
        for (const auto& n: z.second) {
//            printf("Neighbor at (%d, %d, %d): %d\n", n.first.first, n.first.second, z.first, n.second);
            if (n.second == 3) {
                new_data.emplace_back(n.first.first, n.first.second, z.first);
            } else if (n.second == 2) {
                Point3D p { n.first.first, n.first.second, z.first };
                if (std::find(data.begin(), data.end(), p) != data.end()) {
                    // p was active before
                    new_data.push_back(p);
                }
            }
        }
    }
    return new_data;
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
    int result = 0;

    std::vector<Point3D> data;
    int y = 0;
    for (string line; getline(input, line); ) {
        int x = 0;
        for (auto c: line) {
            if (c == '#') {
                data.emplace_back(x, y, 0);
            }
            x++;
        }
        y++;
    }
    for (int cycle = 0; cycle < 6; cycle++) {
//        ::printf("Cycle %d\n", cycle);
        for (const auto& p: data) {
//            printf("Point (%d, %d, %d) active\n", p.x, p.y, p.z);
        }
        data = make_cycle(data);

    }

    result = static_cast<int>(data.size());


    ::printf("Task 1 result: %d\n", result);
    return 0;
}

