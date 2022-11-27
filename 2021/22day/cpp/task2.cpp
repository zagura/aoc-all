/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2021 - Day 22
 *
 *        Version:  0.1.0
 *        Created:  22.12.2021 - 23.02.2022, 06.03.2022
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
#include <cinttypes>

using std::string;
using std::vector;
using std::array;
using std::map;
using std::pair;
using std::make_pair;
using std::stringstream;
struct Point3D {
    Point3D(int64_t X, int64_t Y, int64_t Z) noexcept: x(X), y(Y), z(Z)  {}
    int64_t x = 0;
    int64_t y = 0;
    int64_t z = 0;
    bool operator==(const Point3D& other) {
        return (other.x == x)
               and (other.y == y)
               and (other.z == z);
    }
};
bool inside_range(const std::pair<int, int>& left, const std::pair<int, int>& right);

struct Area3D {
    std::pair<int64_t, int64_t> x_range {};
    std::pair<int64_t, int64_t> y_range {};
    std::pair<int64_t, int64_t> z_range {};
    bool valid = true;
    std::vector<int> history = {};
    Area3D(std::pair<int64_t, int64_t> range_x, std::pair<int64_t, int64_t> range_y, std::pair<int64_t, int64_t> range_z, int on, bool enable = true)
        : x_range(range_x), y_range(range_y), z_range(range_z), valid(enable) {
        history.push_back(0);
        history.push_back(on);
    }
    Area3D(std::pair<int64_t, int64_t> range_x, std::pair<int64_t, int64_t> range_y, std::pair<int64_t, int64_t> range_z, const std::vector<int>& old, int last)
        : x_range(range_x), y_range(range_y), z_range(range_z), valid(true), history(old) {
        history.push_back(last);
    }
    size_t size() const {
        if (!valid) { return 0; }
        return (x_range.second - x_range.first + 1)
               * (y_range.second - y_range.first + 1)
               * (z_range.second - z_range.first + 1);
    }
    int last() const {
        return history.back();
    }
    int prev() const {
        return history.at(history.size() - 2);
    }
    void print() {
        printf("(%" PRId64 ", %" PRId64 ", %" PRId64 ") -> (%" PRId64 ", %" PRId64 ", %" PRId64 "): (%zu) \t%zu/%d/%d\n",
               x_range.first, y_range.first, z_range.first,
               x_range.second, y_range.second, z_range.second,
               size(), history.size(), prev(), history.back());
    }
    bool inside(const Area3D& other) {
        return inside_range(x_range, other.x_range) && inside_range(y_range, other.y_range) &&
               inside_range(z_range, other.z_range);
    }
    bool equal_area(const Area3D& other) {
        return x_range == other.x_range
             && y_range == other.y_range
               && z_range == other.z_range;
    }
};
bool inside_range(const std::pair<int, int>& left, const std::pair<int, int>& right) {
    return (left.first >= right.first && left.second <= right.second);
}


std::pair<int64_t, int64_t> limits (const std::pair<int64_t, int64_t>& r1, const std::pair<int64_t, int64_t>& r2) {
    return std::make_pair(std::max(r1.first, r2.first), std::min(r1.second, r2.second));
}

Area3D commonArea(const Area3D& a1, const Area3D& a2) {
    Area3D area {
        limits (a1.x_range, a2.x_range),
        limits (a1.y_range, a2.y_range),
        limits (a1.z_range, a2.z_range),
        a1.history, a2.history.back()
    };
    if ((area.x_range.second < area.x_range.first)
        || (area.y_range.second < area.y_range.first)
        || (area.z_range.second < area.z_range.first)) {
        return Area3D { {0 , 0},  {0, 0}, {0, 0}, 0, false};
    }
    return area;

}


std::pair<int64_t, int64_t> parse_coords(const std::string& str) {
    std::stringstream stream { str };
    std::string token;
    getline(stream, token, '=');
    getline(stream, token, '.');
    int64_t first = std::stoi(token);
    getline(stream, token);
    int64_t second = std::stoi(token.substr(1));
    return std::make_pair(first, second);
}

int64_t total_area_size(const std::vector<Area3D>& areas) {
    int64_t area = 0;
    for (const auto& a: areas) {
        if (a.last() == 1 && a.prev() == 0) {
            area += a.size();
        } else if (a.prev() == 1) {
            area -= a.size();
        }
    }
    return area;
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

    std::vector<Area3D> data;
    data.reserve(500);
    for (string line; getline(input, line); ) {
        if (line.empty()) { continue; } // skip empty lines
        std::string token;
        std::stringstream line_stream { line };
        std::string action;
        getline(line_stream, action, ' ');
        getline(line_stream, token, ',');
        auto range_x = parse_coords(token);
        getline(line_stream, token, ',');
        auto range_y = parse_coords(token);
        getline(line_stream, token, ',');
        auto range_z = parse_coords(token);
        data.emplace_back(range_x, range_y, range_z, action == "on");
    }
    //    for (auto& el: data) {
    //        el.print();
    //    }

    std::vector<Area3D> old_commons {};
    std::vector<Area3D> commons {};
    for (auto& area: data) {
        for (auto& old_comm: old_commons) {
            if (old_comm.history.back() == 0 && area.history.back() == 0) {
                continue;
            }
            Area3D common_area = commonArea(old_comm, area);
            if (common_area.valid) {
                commons.push_back(common_area);
            }
        }
        for (size_t i = 0; i < commons.size(); i++) {
            bool valid = true;
            for (size_t j = 0; j < commons.size(); j++) {
                if (i != j && commons[i].inside(commons[j])) {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                printf("Add common: ");
                commons[i].print();
                old_commons.push_back(commons[i]);
            }
        }
        if (area.history.back() == 1) {
            old_commons.push_back(area);
        }
        commons.clear();
        printf("Area after step: %" PRId64 "\n", total_area_size(old_commons));
    }


    ::printf("Task 2 result: %" PRId64 "\n", total_area_size(old_commons));
    return 0;
}
