/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  AoC 2025 - Day 9
 *
 *        Version:  1.0
 *        Created:  30.12.2025
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */


#include <iostream>
#include <fstream>
#include <sstream>
#include <string_view>
#include <vector>
#include <cinttypes>
#include <format>
#include <print>
#include <set>
#include <ncurses.h>

using Point = std::pair<uint64_t, uint64_t>;

struct Line {
    uint64_t x1;
    uint64_t x2;
    uint64_t y1;
    uint64_t y2;
    Line(Point p1, Point p2) noexcept {
        // Left to right or down to up
        if (p1.first < p2.first or p1.second < p2.second) {
            x1 = p1.first;
            x2 = p2.first;
            y1 = p1.second;
            y2 = p2.second;
        } else {
            // Reverse otherwise
            x1 = p2.first;
            x2 = p1.first;
            y1 = p2.second;
            y2 = p1.second;
        }
    }
    bool pass_y(uint64_t y) const {
        return y1 < y && y < y2;
    }
    bool pass_x(uint64_t x) const {
        return x1 <= x && x < x2;
    }
    bool is_within_line(uint64_t x, uint64_t y) const {
        return (x1 <= x && x <= x2) && (y1 <= y && y <= y2);
    }
    uint64_t len() const {
        return (y2 - y1) + (x2 - x1);
    }
    bool outside(size_t low_x, size_t high_x, size_t low_y, size_t high_y) const {
        if (x2 < low_x or x1 > high_x) return true;
        if (y2 < low_y or y1 > high_y) return true;
        return false;
    }
};


uint64_t diff(uint64_t a, uint64_t b) {
    if (a < b) {
        return (b - a);
    }
    return (a - b);
}

struct data {
    uint64_t minx, miny, maxx, maxy;
};

void fill_data(data& d, uint64_t x, uint64_t y) {
    if (x < d.minx) {
        d.minx = x;
    }
    if (x > d.maxx) {
        d.maxx = x;
    }
    if (y < d.miny) {
        d.miny = y;
    }
    if (y > d.maxy) {
        d.maxy = y;
    }
}


bool is_inside_shape(uint64_t x, uint64_t y,
                     const std::vector<Line>& hlines,
                     const std::vector<Line>& vlines) {
    // bool inside = false;
    auto count  = std::count_if(hlines.begin(), hlines.end(),
                               [&] (const auto& l) { return (l.pass_x(x) && l.y1 < y); });
                // + std::count_if(vlines.begin(), vlines.end(),
                //                  [&] (const auto& l) { return (l.x1 == x && l.y1 <= y && l.y2 >= y); });
    // auto vertical_count = std::count_if(vlines.begin(), vlines.end(),
    //                                       [&] (const auto& l) { return (l.pass_y(y) && l.x1 < x); })
    //                       + std::count_if(hlines.begin(), hlines.end(),
    //                                         [&] (const auto& l) { return (l.y1 == y && l.x1 < x && x < l.x2 ); });

    // count += std::count_if(vlines.begin(), vlines.end(), [&] (const auto& l) { return l.pass_y(y) and l.x1 == x; });
    auto hline = std::count_if(hlines.begin(), hlines.end(), [&] (const auto& l) { return l.is_within_line(x, y);});
    auto vline = std::count_if(vlines.begin(), vlines.end(), [&] (const auto& l) { return l.is_within_line(x, y);});
    bool in_line = (hline + vline) > 0;
    return ((count) % 2 == 1) or in_line;
}

/*
// std::vector<Point> interior(Point p1, Point p2) {
//     std::vector<Point> ps {};
//     auto x1 = std::min(p1.first, p2.first);
//     auto x2 = std::max(p1.first, p2.first);
//     auto y1 = std::min(p1.second, p2.second);
//     auto y2 = std::max(p1.second, p2.second);
//     // ps.emplace_back(x1, y1);
//     ps.emplace_back(x2, y1);
//     ps.emplace_back(x1, y2);
//     // ps.emplace_back(x2, y2);
//     if (x1 != x2) {
//         x1++;
//         x2--;
//     }
//     if (y1 != y2) {
//         y1++;
//         y2--;
//     }
//     ps.emplace_back(x1, y1);
//     ps.emplace_back(x2, y1);
//     ps.emplace_back(x1, y2);
//     ps.emplace_back(x2, y2);
//     // for (auto x = x1; x <= x2; x++) {
//     //     for (auto y = y1; y <= y2; y++) {
//     //         ps.emplace_back(x, y);
//     //     }
//     // }
//     return ps;
// }
*/
void render(const std::vector<Line>& hlines, const std::vector<Line>& vlines, const std::vector<Point>& points, const data& d) {
    attron(COLOR_PAIR(2));
    int mx, my;
    getmaxyx(stdscr, mx, my);
    for (size_t x = 0; x <= static_cast<size_t>(mx); x++) {
        for (size_t y = 0; y <= static_cast<size_t>(my); y++) {
            if (is_inside_shape(x, y, hlines, vlines)) {
                mvaddch(y, x, ' ');
            }
        }
    }
    // attron(COLOR_PAIR(3));
    // for (const auto& [px, py]: points) {
    //     mvaddch(py, px, ' ');
    // }
    move(0, 0);
}

void curses_init() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(1);

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_BLACK, COLOR_GREEN);
    init_pair(3, COLOR_BLACK, COLOR_RED);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    attron(COLOR_PAIR(1));
}


void curses_finish() {
    attroff(COLOR_PAIR(1));
    getch();
    endwin();
}

class Iter {
public:
    typedef Point value_type;
    Iter(uint64_t x1, uint64_t x2, uint64_t y1, uint64_t y2) {
        low_x = std::min(x1, x2);
        high_x = std::max(x1, x2);
        low_y = std::min(y1, y2);
        high_y = std::max(y1, y2);
        current_x = low_x;
        current_y = low_y;
    }
    Point state() {
        return std::make_pair(current_x, current_y);
    }
    Iter& operator++() {
        if (current_y == high_y) {
            current_x++;
            current_y = low_y;
            return *this;
        }
        if (current_x == low_x or current_x == high_x) {
            current_y++;
            return *this;
        }
        current_y = high_y;
        return *this;
    }
    Iter operator++(int) {
        return ++(*this);
    }
    bool end() {
        return current_x > high_x;
    }
    uint64_t current_x, current_y;
    uint64_t low_x, high_x, low_y, high_y;
};

int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    std::vector<Point> values {};
    for (std::string line; getline(input, line);) {
        uint64_t x = std::stoull(line.substr(0, line.find(',')));
        uint64_t y = std::stoull(line.substr(line.find(',') + 1));
        values.emplace_back(x, y);
    }
    uint64_t max_area = 0;
    data d;
    if (values.empty()) {
        return 1;
    }
    d.minx = d.maxx = values.front().first;
    d.miny = d.maxy = values.front().second;
    std::vector<Line> lines {};
    for (size_t i = 0; i < values.size(); i++) {
        lines.emplace_back(values[i], values[(i + 1) % values.size()]);
    }
    std::vector<Line> horizontal {};
    std::copy_if(lines.begin(), lines.end(), std::back_inserter(horizontal),
                 [](const auto l) { return (l.y1 == l.y2); });
    std::vector<Line> vertical {};
    std::copy_if(lines.begin(), lines.end(), std::back_inserter(vertical),
                 [](const auto l) { return (l.x1 == l.x2); });

    for (const auto& l: lines) {
        std::println("Line len: {}", l.len());
    }
    // std::println("Horizontal (size): {}", horizontal.size());
    for (size_t i = 0; i < values.size(); i++) {
        std::println("Starting point {}", i);
        std::set<Point> outsiders {};
        for (size_t j = i + 1; j < values.size(); j++) {
            auto [x1, y1] = values[i];
            auto [x2, y2] = values[j];
            uint64_t dx = (diff(x1, x2) + 1);
            uint64_t dy = (diff(y1, y2) + 1);
            if (dx == 1 or dy == 1) {
                continue;
            }
            uint64_t area = dx * dy;
            fill_data(d, x1, y1);
            if (area > max_area) {
                // std::println("Checking area {} from pair {}->{}", area, i, j);
                Iter it(x1, x2, y1, y2);
                bool outside = false;
                for (const auto& l: lines) {
                    if (not l.outside(it.low_x + 1, it.high_x - 1,
                                      it.low_y + 1, it.high_y - 1)) {
                        outside = true;
                        break;
                    }
                }
                if (outside) {
                    continue;
                }
                for (auto p: outsiders) {
                    if ((it.low_x < p.first && p.first < it.high_x)
                        and (it.low_y < p.second && p.second < it.high_y)) {
                            // std::println("Outsider ({}, {})", p.first, p.second);
                            outside = true;
                            break;
                    }
                }
                if (outside) {
                    continue;
                }
                // for (const auto& p: interior(values[i], values[j])) {
                for (; not it.end(); ++it) {
                    auto p = it.state();
                    // std::println("Iterator: [{}, {}], from [{}, {}] -> [{}, {}]", p.first, p.second, it.low_x, it.low_y, it.high_x, it.high_y);
                    if (not is_inside_shape(p.first, p.second, horizontal, vertical)) {
                        // std::println("Point ({}, {})", p.first, p.second);
                        outsiders.emplace(p);
                        outside = true;
                        break;
                    }
                }
                if (outside) {
                    continue;
                }
                std::println("({} -> {}) [{}, {}] -> [{}, {}]: {} x {} == {}", i, j, x1, y1, x2, y2, diff(x1, x2) + 1, diff(y1, y2) + 1, area);
                max_area = area;
            }
        }
        std::println("Outsiders size: {}", outsiders.size());
    }
    // getch();
    // curses_init();
    // render(horizontal, vertical, values, d);
    // curses_finish();
    std::println("({}, {}), y: ({}, {})", d.minx, d.maxx, d.miny, d.maxy);
    uint64_t total = max_area;
    ::printf("Task 1 result: %" PRIu64 "\n", total);
    return 0;
}
