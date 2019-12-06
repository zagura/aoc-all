/*
 * =====================================================================================
 *
 *       Filename:  task2.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03.12.2019 22:07:15
 *
 *         Author:  Michał Zagórski (zagura), <mzagorsk@student.agh.edu.pl>
 *   Organization:  AGH University of Science and Technology, Kraków
 *
 * =====================================================================================
 */
/* require C++17 */
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <optional>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::vector;
using std::getline;
using std::optional;
using std::pair;
using std::stringstream;

struct Point {
    int x;
    int y;
    Point(int a, int b): x(a),y(b) {}
    Point& add(const Point& other) {
        x += other.x;
        y += other.y;
        return (*this);
    }
};

bool ordered_triple(int a, const int b, const int c) {
    return ((a < b) && (b < c));
}

bool between(int middle, const int border1, const int border2) {
    return (ordered_triple(border1, middle, border2)
         || ordered_triple(border2, middle, border1));
}

bool x_between(int x, const Point& p1, const Point& p2) {
    return between(x, p1.x, p2.x);
}

bool y_between(int y, const Point& p1, const Point& p2) {
    return between(y, p1.y, p2.y);
}


int abs(int a) {
    if (a < 0) {
        a *= -1;
    }
    return a;
}

size_t len(const Point& p1, const Point& p2) {
    size_t xdiff = abs(p1.x - p2.x);
    size_t ydiff = abs(p1.y - p2.y);
    return xdiff + ydiff;
}


optional<Point> crosspoint(const Point& begin1, const Point& end1,
                           const Point& begin2, const Point& end2) {
    int cross_x = 0;
    int cross_y = 0;
    // Line 1 is vertical
    if (begin1.x == end1.x) {
        cross_x = begin1.x;
        cerr << __LINE__ << "  l1(x): " << cross_x << endl;
        // second line is horizontal
        if (begin2.y == end2.y) {
            cross_y = begin2.y;
            cerr << __LINE__ << "  l2(y): " << cross_y << endl;
            cerr << (int)x_between(cross_x, begin2, end2) << " "
                 << (int)y_between(cross_y, begin1, end1) << endl;
            if (x_between(cross_x, begin2, end2)
                && y_between(cross_y, begin1, end1)) {
                    return Point(cross_x, cross_y);
            }
        }
        else {
            return {};
        }
    } else {
        if (begin1.y == end1.y) {
            cross_y = begin1.y;
            cerr << __LINE__ << " l1(y): " << cross_y << endl;
            if (begin2.x == end2.x) {
                cross_x = begin2.x;
                cerr << __LINE__ << " l2(x): " << cross_x << endl;
                cerr << (int)x_between(cross_x, begin1, end1) << " "
                     << (int)y_between(cross_y, begin2, end2) << endl;
                if (x_between(cross_x, begin1, end1)
                    && y_between(cross_y, begin2, end2)) {
                        return Point(cross_x, cross_y);
                }
            } else {
                return {};
            }
        }
    }
    return {};
}

vector<Point> get_path(stringstream& line) {
    vector<Point> path {};
    path.reserve(200);
    path.push_back(Point(0, 0));
    for (string mov; getline(line, mov, ','); ) {
        if (mov.size() > 1) {
            stringstream  expr { mov };
            char direction;
            int distance;
            expr >> direction >> distance;
            direction = std::tolower(direction);
            Point p (0, 0);
            Point last = path.back();
            switch(direction) {
                case 'u':
                    p = Point(0, distance);
                    break;
                case 'd':
                    p = Point(0, -1 * distance);
                    break;
                case 'l':
                    p = Point(-1 * distance, 0);
                    break;
                case 'r':
                    p = Point(distance, 0);
                    break;
            }
            path.push_back(last.add(p));
        }
    }
    return path;
}

vector<std::pair<Point, size_t>> get_crosspoints(const vector<Point>& path1, const vector<Point>& path2) {
    vector<std::pair<Point, size_t>> crosspoints;
    size_t p1_distance = 0;
    size_t p2_distance = 0;
    for (size_t i1 = 0; i1 < path1.size() - 1; i1 += 1) {
        Point p1_b = path1.at(i1);
        Point p1_e = path1.at(i1 + 1);
        p2_distance = 0;
        for (size_t i2 = 0; i2 < path2.size() - 1; i2 += 1) {
            Point p2_b = path2.at(i2);
            Point p2_e = path2.at(i2 + 1);
            optional<Point> cross = crosspoint(p1_b, p1_e, p2_b, p2_e);
            if (cross) {
                Point target = cross.value();
                size_t cross_distance = len(target, p1_b);
                cross_distance += len(target, p2_b);
                cross_distance += p1_distance;
                cross_distance += p2_distance;
                crosspoints.push_back(std::make_pair(target, cross_distance));
            }
            p2_distance += len(p2_b, p2_e);
        }
        p1_distance += len(p1_b, p1_e);
    }
    return crosspoints;
}


void print_path(vector<Point>& path) {
    for (auto& p: path) {
        cout << "x: " << p.x << " y: " << p.y << '\n';
    }
    cout << std::endl << std::endl;
}

int main() {
    string line;
    getline(std::cin, line);
    stringstream ss (line);
    vector<Point> first = get_path(ss);
    getline(std::cin, line);
    ss = stringstream(line);
    vector<Point> second = get_path(ss);
    print_path(first);
    print_path(second);
    vector<pair<Point, size_t>> crosspoints = get_crosspoints(first, second);
    std::sort(crosspoints.begin(), crosspoints.end(), 
            [](pair<Point, size_t>& pair1, pair<Point, size_t>& pair2) {
//        return ((abs(p1.x) + abs(p1.y)) < (abs(p2.x) + abs(p2.y)));
                return pair1.second < pair2.second;
        });
    cout << "\nFinal crosspoints: " <<  '\n';
    for (auto& cp: crosspoints) {
        cout << cp.first.x << ',' << cp.first.y 
             << ":  " << abs(cp.first.x) + abs(cp.first.y) 
             << ":  " << cp.second << std::endl;
    }
    return 0;
}
