/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
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
struct Point4D {
    Point4D(int X, int Y, int Z, int W) noexcept: x(X), y(Y), z(Z), w(W) {}
    int x = 0;
    int y = 0;
    int z = 0;
    int w = 0;
    bool operator==(const Point4D& other) {
        return (other.x == x)
               and (other.y == y)
               and (other.z == z)
               and (other.w == w);
    }
};

std::array<int, 3> dim_change = { -1, 0, 1};

vector<Point4D> make_cycle(vector<Point4D>& data) {
    vector<Point4D> new_data {};
    // z -> [(x,y) -> int]
    std::map<pair<int, int>, map<pair<int, int>, int>> neigh {};
//    neigh.reserve(data.size() * 2);
    new_data.reserve(data.size());

    for (const auto& p: data) {
        for (int dx: {-1, 0, 1}) {
            for (int dy: {-1, 0, 1}) {
                for (int dz: {-1, 0, 1}) {
                    for (int dw: {-1, 0, 1}) {
                    // All three values are 0, we are at the same point as p
                        if ((dx | dy | dz | dw) != 0) {
                            neigh[make_pair(p.z + dz, p.w + dw)][make_pair(p.x + dx, p.y + dy)]++;
                        }
                    }
                }
            }
        }
    }

    for (auto& z: neigh) {
        for (const auto& n: z.second) {
//            printf("Neighbor at (%d, %d, %d): %d\n", n.first.first, n.first.second, z.first.first, n.second);
            if (n.second == 3) {
                new_data.emplace_back(n.first.first, n.first.second, z.first.first , z.first.second);
            } else if (n.second == 2) {
                Point4D p { n.first.first, n.first.second, z.first.first, z.first.second };
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

    std::vector<Point4D> data;
    int y = 0;
    for (string line; getline(input, line); ) {
        int x = 0;
        for (auto c: line) {
            if (c == '#') {
                data.emplace_back(x, y, 0, 0);
            }
            x++;
        }
        y++;
    }
    for (int cycle = 0; cycle < 6; cycle++) {
//        ::printf("Cycle %d\n", cycle);
//        for (const auto& p: data) {
////            printf("Point (%d, %d, %d) active\n", p.x, p.y, p.z);
//        }
        data = make_cycle(data);

    }

    result = static_cast<int>(data.size());


    ::printf("Task 1 result: %d\n", result);
    return 0;
}

