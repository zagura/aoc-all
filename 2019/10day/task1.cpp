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

struct Point {
    int x, y;
    Point(int x_param, int y_param) noexcept : x(x_param),y(y_param) {}
    bool collide(const Point& target,const Point& collider) const {
        if (target.y == y) {
            if (collider.y != y) return false;
            if ((target.x > collider.x && collider.x > x)
                    || (target.x < collider.x && collider.x < x)) {
                    return true;
            }
            return false;
        } else if (collider.y == y) {
            return false;
        }
        if (target.x == x) {
            if (collider.x != x) return false;
            if ((target.y > collider.y && collider.y > y)
                    || (target.y < collider.y && collider.y < y)) {
                    return true;
            }
            return false;
        } else if (collider.x == x) {
            return false;
        }
        int y_target = target.y - this->y;
        int y_collider = collider.y - this->y;
        int proportion = y_target / y_collider;
        if (proportion > 0 and y_target % y_collider == 0) {
            int x_target = target.x - this->x;
            int x_collider = collider.x - this->x;
            if (x_target % x_collider == 0 and x_target / x_collider == proportion) {
                return true;
            }
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

pair<Point,int> get_best(vector<Point>& asteroid_map) {
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
            best.print();
            cout << endl;
            for (auto& t: targets) {
                cout <<  "  ";
                t.print();
                cout << endl;
            }
        }
    }
    return make_pair(best, max_sight);
}


int main() {
    vector<Point> asteroid_map = read_map();
    auto best = get_best(asteroid_map);
    cout << "Part 1: " << best.second << endl;
    return 0;
}
