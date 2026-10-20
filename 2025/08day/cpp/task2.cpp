/*
 * =====================================================================================
 *
 *       Filename:  task2.cpp
 *
 *    Description:  AoC 2025 - Day 8
 *
 *        Version:  1.0
 *        Created:  27.12.2025
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */


#include <iostream>
#include <fstream>
#include <print>
#include <sstream>
#include <string_view>
#include <vector>
#include <cinttypes>
#include <format>
#include <tuple>
#include <map>
struct Point {
    int id = 0;
    int x = 0;
    int y = 0;
    int z = 0;
};

Point get_point(std::string line, int id) {
    std::stringstream data { line };
    std::vector<int> nums;
    for (std::string token; getline(data, token, ','); ) {
        nums.push_back(std::stoi(token));
    }
    Point p;
    p.id = id;
    if (nums.size() != 3) {
        throw std::runtime_error(std::format("Invalid size {}", nums.size()));
    }
    p.x = nums[0];
    p.y = nums[1];
    p.z = nums[2];
    return p;
}

struct Edge {
    std::pair<int, int> ids;
    uint64_t distance;
    Edge(int i, int j, uint64_t d) noexcept : ids(i, j), distance(d) {
        // std::println("({}, {}) -> dist({})", i, j, d);
    }
};

uint64_t diff(int a, int b) {
    if (a < b) {
        return (b - a);
    }
    return (a - b);
}

uint64_t get_dist(Point p1, Point p2) {
    uint64_t d = 0;
    uint64_t dx = diff(p1.x, p2.x);
    uint64_t dy = diff(p1.y, p2.y);
    uint64_t dz = diff(p1.z, p2.z);
    d += (dx * dx);
    d += (dy * dy);
    d += (dz * dz);
    return d;
}

int connections = 1000;

// void rewrite(std::vector<int> fu, int old, int new_val) {
//     for (auto& i: fu) {
//         if (i == old) {
//             i = new_val;
//         }
//     }
// }

int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc >= 2) {
        input = std::ifstream { argv[1] };
        if (argc == 3) {
            connections = std::stoi(argv[2]);
        }
    }
    std::vector<Point> points {};
    int id = 0;
    for (std::string line; getline(input, line); id++) {
        if (line.empty()) {
            continue;
        }
        points.push_back(get_point(line, id));
    }
    std::vector<Edge> edges {};
    std::vector<int> fu {};
    fu.resize(points.size());
    for (size_t i = 0; i < fu.size(); i++) {
        fu[i] = i;
    }
    for (size_t i = 0; i < points.size(); i++) {
        for (size_t j = i + 1; j < points.size(); j++) {
            edges.emplace_back(i, j, get_dist(points[i], points[j]));
        }
    }
    std::sort(edges.begin(), edges.end(), [](Edge e1, Edge e2) { return e1.distance < e2.distance; });
    auto edge = edges.begin();
    for (int step = 0; edge != edges.end(); edge++) {
        auto [l, r] = edge->ids;
        std::println("{} - E: ({}) [{}, {}], u1 {}, u2 {}", step, edge->distance, l, r, fu[l], fu[r]);
        step++;
        if (fu[l] == fu[r]) {
            continue;
        } else {
            // replace old -> new: (begin, end, old, new)
            auto left = fu[l];
            auto right = fu[r];
            auto lsize = std::count_if(fu.begin(), fu.end(), [&](const auto& el) { return el == left; });
            auto rsize = std::count_if(fu.begin(), fu.end(), [&](const auto& el) { return el == right; });
            if (right < left) {
                // fu[l] = fu[r];
                std::replace(fu.begin(), fu.end(), left, right);
            } else {
                // fu[r] = fu[l];
                std::replace(fu.begin(), fu.end(), right, left);
            }
            size_t new_lsize = std::count_if(fu.begin(), fu.end(), [&](const auto& el) { return el == left; });
            size_t new_rsize = std::count_if(fu.begin(), fu.end(), [&](const auto& el) { return el == right; });
            if (new_lsize + new_rsize == fu.size()) {
                auto& lp = points[l];
                auto& rp = points[r];
                std::println("Task 2: {}x{} == {}", lp.x, rp.x, lp.x * rp.x);
                break;
            }
            // std::println("Merging two sets of size: {} and {} into {} and {}", lsize, rsize, new_lsize, new_rsize);
        }
    }
    std::map<int, int> sizes {};
    for (const auto& lowest: fu) {
        sizes[lowest]++;
    }
    std::vector<int> counts {};
    for (auto [k, v]: sizes) {
        if (v > 1) {
            counts.push_back(v);
        }
    }
    std::sort(counts.begin(), counts.end());
    for (auto& c: counts) {
        std::print("{} ", c);
    }
    size_t total = 1;
    auto it = counts.rbegin();
    for (int i = 0; i < 3 && i < static_cast<int>(counts.size()); i++) {
        total *= *it;
        it++;
    }
    ::printf("\nTask 1 result: %" PRIu64 "\n", total);
    return 0;
}
