/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2022 - Day 14
 *
 *        Version:  0.1.0
 *        Created:  15.12.2022
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <sstream>
#include <algorithm>
#include <array>
#include <map>
#include <vector>
#include <iomanip>
#include <bitset>
using std::string;
using std::vector;
using std::array;
using std::map;
using std::stringstream;
using Area = std::vector<std::vector<char>>;
using Point = std::pair<int, int>;

void update_range(std::pair<int, int>& range, int val) {
    if (val < range.first) {
        range.first = val;
    }
    if (val > range.second) {
        range.second = val;
    }
}

std::list<std::pair<int, int>> tokenize(std::string& line,
                                        std::pair<int, int>& xs,
                                        std::pair<int, int>& ys) {
    std::list<std::pair<int, int>> result;
    std::stringstream line_stream { line };
    size_t iter = 1;
    for (std::string coords; getline(line_stream, coords, ' '); iter++) {
        if (iter % 2) {
            int x = std::stoi(coords.substr(0, coords.find(',')));
            int y = std::stoi(coords.substr(coords.find(',') + 1));
            result.emplace_back(x, y);
            update_range(xs, x);
            update_range(ys, y);
        }
    }
    return result;
}

void draw_line(Area& area,
               const Point& p1,
               const Point& p2,
               const std::pair<int, int>& xs,
               const std::pair<int, int>& ys) {
//    ::printf("Draw: (%d, %d) -> (%d,%d)\n", p1.first, p1.second, p2.first, p2.second);
    auto x_start = std::min(p1.first, p2.first) - xs.first;
    auto x_end = std::max(p1.first, p2.first) - xs.first;
    auto y_start = std::min(p1.second, p2.second) - ys.first;
    auto y_end = std::max(p1.second, p2.second) - ys.first;
    if (x_start != x_end) {
        for (int x = x_start; x <= x_end; x++) {
            area[x][y_start] = '#';
        }
    } else if (y_start != y_end) {
        for (int y = y_start; y <= y_end; y++) {
            area[x_start][y] = '#';
        }
    }
}


void print_area(Area& area) {
    for (size_t x = 0; x < area.front().size(); x++) {
        for (size_t y = 0; y < area.size(); y++) {
            printf("%c", area[y][x]);
        }
        printf("\n");
    }
}

Area
fill_area(const std::pair<int, int> xs,
          const std::pair<int, int> ys,
          const std::vector<std::list<std::pair<int, int>>>& paths) {
    Area area (xs.second - xs.first);
    for (auto& row: area) {
        row.resize(ys.second - ys.first);
        std::fill(row.begin(), row.end(), '.');
    }
    for (auto& path: paths) {
        auto prev = path.begin();
        auto next = path.begin();
        ++next;
        for (; next != path.end(); ++prev, ++next) {
            draw_line(area, *prev, *next, xs, ys);
        }
    }
    return area;
}
bool drop(const Point& start, Area& area) {
    Point op1 = start;
    // We reach edge of the area;
    if (start.first == 0 || start.first == (area.size() - 1)|| (start.second == area[0].size() - 1)) {
        printf("Start: (%d, %d)\n", start.first, start.second);
        return false;
    }
    op1.second++;
    Point op2 = op1;
    Point op3 = op1;
    op2.first--;
    op3.first++;
    if (area[op1.first][op1.second] == '.') {
//        area[op1.first][op1.second] = 'o';
        return drop(op1, area);
    } else if (area[op2.first][op2.second] == '.') {
//        area[op2.first][op2.second] = 'o';
        return drop(op2, area);
    } else if (area[op3.first][op3.second] == '.') {
//        area[op3.first][op3.second] = 'o';
        return drop(op3, area);
    } else {
        if (area[start.first][start.second] == '.') {
            area[start.first][start.second] = 'o';
            return true;
        }
    }
    return false;
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

    std::pair<int, int> xs { 1000, 0 };
    std::pair<int, int> ys { 1000, 0 };
    std::vector<std::list<std::pair<int, int>>> paths;
    std::vector<std::vector<char>> area;
    for (std::string line; getline(input, line); ) {
        if (line.empty()) {
            continue;
        }
        std::list<std::pair<int, int>> points = tokenize(line, xs, ys);
        paths.push_back(points);
        for (const auto& p: points) {
            ::printf("(%d,%d) ", p.first, p.second);
        }
        printf("\n");
    }
    printf("X: [%d, %d]\n", xs.first, xs.second);
    printf("Y: [%d, %d]\n", ys.first, ys.second);
    const int offset = 2;
    xs.first -= offset;
    xs.second += offset;
    ys.first = 0;
    ys.second += offset;
    area = fill_area(xs, ys, paths);
    print_area(area);
    Point start = std::make_pair(500 - xs.first, 0);
    size_t count = 0;
    while (drop(start, area)) {
        count++;
        printf("\n%zu\n", count);
        print_area(area);
//        if (count == 30) {
//            break;
//        }
    }

    ::printf("Task 1 result: %zu\n", count);
    return 0;
}

