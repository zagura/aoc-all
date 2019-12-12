/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  07.12.2019
 *
 *         Author:  Michał Zagórski (zagura), <mzagorsk@student.agh.edu.pl>
 *   Organization:  AGH University of Science and Technology, Kraków
 *
 * =====================================================================================
 */
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <array>
#include <algorithm>
#include <cmath>

using std::getline;
using std::istringstream;
using std::stringstream;
using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::array;
using std::pair;
using std::make_pair;
using std::next_permutation;

using coord = int;
struct Point;
int mul(const Point& p1, const Point& p2);
int scalar_mul(const Point& p1, const Point& p2);
struct Point {
    int x, y;
    Point(int x_param, int y_param) noexcept : x(x_param),y(y_param) {}
    int size() const {
        return (x * x) + (y * y);
    }
    bool collide(const Point& target,const Point& collider) const {
        Point vec1(target.x - x, target.y - y);
        Point vec2(collider.x - x, collider.y - y);
        int result = mul(vec1, vec2);
        if (vec1.size() < vec2.size()) {
            return false;
        }
        if (result == 0 and scalar_mul(vec1, vec2) > 0) {
            return true;
//            if (vec1.x % vec2.x == 0 and vec1.y % vec2.y == 0
//                   and (vec1.x / vec2.x) == (vec1.y / vec2.y)) {
//                return true;
//            }
        }
        return false;
    }
    bool operator==(const Point& other) const {
        return x == other.x and y == other.y;
    }
    bool operator!=(const Point& other) const {
        return x != other.x or y != other.y;
    }
    void print() {
        cout << '(' << x << ',' << y << ')';
    }
};

int mul (const Point& p1, const Point& p2) {
    return (p1.x * p2.y) - (p1.y * p2.x);
}

int scalar_mul(const Point& p1, const Point& p2) {
    return (p1.x * p2.x) + (p1.y * p2.y);
}


vector<Point> read_map() {
    vector<Point> asteroid_map;
    int y = 0;
    for (string row; getline(std::cin, row); y++) {
        int max_x = row.size();
        for (int x = 0; x < max_x; x++) {
            if (row[x] == '#') {
                asteroid_map.emplace_back(x, y);
            }
        }
    }
    return asteroid_map;
}

pair<Point,int> get_best(vector<Point>& asteroid_map, vector<Point>& best_detect) {
    Point best(0,0);
    int max_sight = 0;
    for (Point& asteroid: asteroid_map) {
        vector<Point> targets;
        int current_sight = 0;
        for (Point& target: asteroid_map) {
            if (target != asteroid) {
                bool sight = true;
                for(Point& other: asteroid_map) {
                    if (other != asteroid && other != target) {
                        if (asteroid.collide(target, other)) {
                            sight = false;
                            break;
                        }
                    }
                }
                if (sight) {
                    targets.push_back(target);
                    current_sight += 1;
                }
            }
        }
        if (current_sight > max_sight) {
            max_sight = current_sight;
            best = asteroid;
            best_detect = targets;
        }
    }
    return make_pair(best, max_sight);
}

int get_200(vector<Point>& detected, Point& station) {
    vector<pair<Point, long double>> angles;
    for (Point& p: detected) {
        Point base (0, -1);
        Point vec (p.x - station.x, p.y - station.y);
        long double cos = static_cast<long double>(scalar_mul(base, vec)) /
                static_cast<long double>(sqrtl(base.size()) * sqrtl(vec.size()));
        if (mul(base, vec) < 0) { cos = -3 - cos; };
        angles.emplace_back(p, cos);
    }
    std::sort(detected.begin(), detected.end(), [&station](Point& left, Point& right) {
        Point base (0, -1);
        Point vec1 (left.x - station.x, left.y - station.y);
        Point vec2 (right.x - station.x, right.y - station.y);
        long double cos1 = static_cast<long double>(scalar_mul(base, vec1))
                / static_cast<long double>((sqrtl(base.size()) * sqrtl(vec1.size())));
        long double cos2 = static_cast<long double>(scalar_mul(base, vec2))
                / static_cast<long double>((sqrtl(base.size()) * sqrtl(vec2.size())));
        if (mul(base, vec1) < 0) { cos1 = - 3 - cos1; }
        if (mul(base, vec2) < 0) { cos2 = - 3 - cos2; }
        return cos1 > cos2;
    });
    std::sort(angles.begin(), angles.end(), [](auto& left, auto& right) {
        return left.second > right.second;
    });
    int i = 0;
    for (auto& angle: angles) {
        cout << ++i << "  ";
        angle.first.print();
        if (angle.first != detected[i-1]) {
            cout << " Difference ";
        }
        cout << " :  " << angle.second;
        cout << endl;
    }
//    Point p = detected.at(199);
    Point p = detected.front();
    return p.x * 100 + p.y;
}

void print_map(vector<Point> asteroid_map, Point& station) {
    int max_x, max_y;
    for (Point& p: asteroid_map) {
        if (p.x > max_x) {
            max_x = p.x;
        }
        if (p.y > max_y) {
            max_y = p.y;
        }
    }
    vector<vector<char>> output_map(max_y + 1, vector<char>(max_x + 1, ' '));
    for (Point& p: asteroid_map) {
        output_map[p.y][p.x] = '1';
    }
    output_map[station.y][station.x] = '8';
    for (auto& vec: output_map) {
        for (auto& c: vec) {
            cout << c;
        }
        cout << endl;
    }
    cout << endl << endl;
}

int main() {
    vector<Point> asteroid_map = read_map();
    vector<Point> detected;
    auto best = get_best(asteroid_map, detected);
    cout << "Part 1: " << best.second << endl;
    int result = get_200(detected, best.first);
    print_map(detected, best.first);
//    cout << "Part 2: " << get_200(detected, best.first) << endl;
    return 0;
}
