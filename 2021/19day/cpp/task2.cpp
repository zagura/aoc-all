/*
 * =====================================================================================
 *
 *       Filename:  task2.cpp
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
    int global_id { -1 };
    Beacon(int _x, int _y, int _z) : x(_x), y(_y), z(_z), scanner_id(-1), line_no(-1), global_id(-1) {}
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
        global_id = -1;
    }

//    Beacon (const Beacon& b) = default;
//    Beacon(const Beacon& b) {
//        x = b.x;
//        y = b.y;
//        z = b.z;
//        scanner_id = b.scanner_id;
//        line_no = b.line_no;
//        global_id = b.global_id;
//    }
    Beacon(): x(0), y(0), z(0), scanner_id(-1), line_no(-1), global_id(-1) {}

    void set_gid(int id) {
        global_id = id;
    }
    size_t dist(const Beacon& other) {
        return diff(other.x, x) + diff(other.y, y) + diff(other.z, z);
    }
    size_t m_dist(const Beacon& other) {
        return abs(other.x - x) + abs(other.y - y) + abs(other.z - z);
    }
    std::string str() const {
        return "("
               + std::to_string(this->x) + ","
               + std::to_string(this->y) + ","
               + std::to_string(this->z) + ")";
    }
    static Beacon move_right(Beacon source) noexcept {

        int tmp = source.z;
        source.z = source.y;
        source.y = source.x;
        source.x = tmp;
        return source;
    }
    static Beacon mirror_x(Beacon source) noexcept {
        source.x *= (-1);
        return source;
    }
    static Beacon mirror_y(Beacon source) noexcept {
        source.y *= (-1);
        return source;
    }
    static Beacon mirror_z(Beacon source) noexcept {
        source.z *= -1;
        return source;
    }
    static Beacon rotate(Beacon source) noexcept {
        auto tmp_x = source.x;
        source.x = source.z;
        source.z = tmp_x;
        return source;
    }
    void translate(int mov_x, int mov_y, int mov_z) noexcept {
        x += mov_x;
        y += mov_y;
        z += mov_z;
    }
    void translate(const Beacon& p) noexcept {
        translate(p.x, p.y, p.z);
    }


};
//template <typename T>
std::array<std::function<Beacon(Beacon)>, 24> transformations {{
    { [](Beacon b) noexcept { return b; }},
    { [](Beacon b) noexcept { return Beacon::move_right(b); }},
    { [](Beacon b) noexcept { return Beacon::move_right(Beacon::move_right(b)); }},

    { [](Beacon b) noexcept { return Beacon::mirror_x(b); }},
    { [](Beacon b) noexcept { return Beacon::mirror_y(b); }},
    { [](Beacon b) noexcept { return Beacon::mirror_z(b); }},
    { [](Beacon b) noexcept { return Beacon::mirror_x(Beacon::mirror_y(Beacon::mirror_z((b)))); }},
    { [](Beacon b) noexcept { return Beacon::mirror_x(Beacon::mirror_y(b)); }},
    { [](Beacon b) noexcept { return Beacon::mirror_x(Beacon::mirror_z(b)); }},
    { [](Beacon b) noexcept { return Beacon::mirror_y(Beacon::mirror_z(b)); }},

    { [](Beacon b) noexcept { return Beacon::move_right(Beacon::mirror_x(b)); }},
    { [](Beacon b) noexcept { return Beacon::move_right(Beacon::mirror_y(b)); }},
    { [](Beacon b) noexcept { return Beacon::move_right(Beacon::mirror_z(b)); }},
    { [](Beacon b) noexcept { return Beacon::move_right(Beacon::mirror_x(Beacon::mirror_y(Beacon::mirror_z((b))))); }},
    { [](Beacon b) noexcept { return Beacon::move_right(Beacon::mirror_x(Beacon::mirror_y(b))); }},
    { [](Beacon b) noexcept { return Beacon::move_right(Beacon::mirror_x(Beacon::mirror_z(b))); }},
    { [](Beacon b) noexcept { return Beacon::move_right(Beacon::mirror_y(Beacon::mirror_z(b))); }},

    { [](Beacon b) noexcept { return Beacon::move_right(Beacon::move_right(Beacon::mirror_x(b))); }},
    { [](Beacon b) noexcept { return Beacon::move_right(Beacon::move_right(Beacon::mirror_y(b))); }},
    { [](Beacon b) noexcept { return Beacon::move_right(Beacon::move_right(Beacon::mirror_z(b))); }},
    { [](Beacon b) noexcept { return Beacon::move_right(Beacon::move_right(Beacon::mirror_x(Beacon::mirror_y(Beacon::mirror_z((b)))))); }},
    { [](Beacon b) noexcept { return Beacon::move_right(Beacon::move_right(Beacon::mirror_x(Beacon::mirror_y(b)))); }},
    { [](Beacon b) noexcept { return Beacon::move_right(Beacon::move_right(Beacon::mirror_x(Beacon::mirror_z(b)))); }},
    { [](Beacon b) noexcept { return Beacon::move_right(Beacon::move_right(Beacon::mirror_y(Beacon::mirror_z(b)))); }},

//    { [](Beacon b) noexcept { return Beacon::rotate(b); }},
//    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::move_right(b)); }},
//    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::move_right(Beacon::move_right(b))); }},

//    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::mirror_x(b)); }},
//    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::mirror_y(b)); }},
//    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::mirror_z(b)); }},
//    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::mirror_x(Beacon::mirror_y(Beacon::mirror_z((b))))); }},
//    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::mirror_x(Beacon::mirror_y(b))); }},
//    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::mirror_x(Beacon::mirror_z(b))); }},
//    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::mirror_y(Beacon::mirror_z(b))); }},

//    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::move_right(Beacon::mirror_x(b))); }},
//    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::move_right(Beacon::mirror_y(b))); }},
//    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::move_right(Beacon::mirror_z(b))); }},
//    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::move_right(Beacon::mirror_x(Beacon::mirror_y(Beacon::mirror_z((b)))))); }},
//    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::move_right(Beacon::mirror_x(Beacon::mirror_y(b)))); }},
//    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::move_right(Beacon::mirror_x(Beacon::mirror_z(b)))); }},
//    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::move_right(Beacon::mirror_y(Beacon::mirror_z(b)))); }},

//    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::move_right(Beacon::move_right(Beacon::mirror_x(b)))); }},
//    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::move_right(Beacon::move_right(Beacon::mirror_y(b)))); }},
//    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::move_right(Beacon::move_right(Beacon::mirror_z(b)))); }},
//    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::move_right(Beacon::move_right(Beacon::mirror_x(Beacon::mirror_y(Beacon::mirror_z((b))))))); }},
//    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::move_right(Beacon::move_right(Beacon::mirror_x(Beacon::mirror_y(b))))); }},
//    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::move_right(Beacon::move_right(Beacon::mirror_x(Beacon::mirror_z(b))))); }},
//    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::move_right(Beacon::move_right(Beacon::mirror_y(Beacon::mirror_z(b))))); }},

}};

size_t m_dist(const Beacon& b1, const Beacon& b2) {
    return abs(b1.x - b2.x) + abs(b1.y - b2.y) + abs(b1.z - b2.z);
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

    std::vector<std::vector<Beacon>> scanners;
    scanners.reserve(100);
    int scanner_id = -1;
    int line_no = 0;
    std::map<int, Beacon> points {};
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
        Beacon b(line, scanner_id, line_no);
        scanners.back().push_back(b);
        points.emplace(line_no, b);
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
//    for (auto& [line_no, beacon]: points) {
//        printf("global id: %d\n", beacon.global_id);
//    }
    size_t result = 0;
    std::map<size_t, int> intersects {};
    std::vector<std::set<int>> global_ids {};
    for (auto& n1: neighbors) {
        printf("Line_no %d\n", n1.first);
        for (auto& n2: neighbors) {
            if (n1.first < n2.first) {
                std::vector<int> intersect {};
                std::set_intersection(n1.second.begin(), n1.second.end(),
                                      n2.second.begin(), n2.second.end(),
                                      std::back_inserter(intersect));
                if (intersect.size() > 1) {
                    /// For intersect.size() == 1, there would be two ends
                    /// of the same section
                    intersects[intersect.size()]++;
                    printf("Common points: %d (%d) [%d] and %d (%d) [%d]: %zu\n", n1.first,
                           points[n1.first].scanner_id , points[n1.first].global_id, n2.first,
                           points[n2.first].scanner_id, points[n2.first].global_id, intersect.size());
                // Assign global beacon id to both beacons
                    int gid = points[n1.first].global_id;
                    if (gid == -1) {
//                        printf("New global id\n");
                        gid = global_ids.size();
                        points[n1.first].global_id = gid;
                        global_ids.emplace_back();
                        global_ids[gid].insert(n1.first);
                    }
                    points[n2.first].global_id = gid;
                    global_ids[gid].insert(n2.first);
                }
//                for (size_t i = 0; i < global_ids.size(); ++i) {
//                    auto& id_set = global_ids[i];
//                    if (id_set.contains(n1.first)) {
//                        if (!id_set.contains(n2.first)) {
//                            id_set.insert(n2.first);
//                            points[n2.first].set_gid(i);
//                        }
//                    }
//                }
            }
        }
    }
    for (const auto& gid_set: global_ids) {
        printf("Global id %d:", points[*gid_set.begin()].global_id);
        for (auto& el: gid_set) {
            printf(" %d", el);
        }
        printf("\n");
    }
    size_t single_points = 0;
    for (auto& [id, point]: points) {
        if (point.global_id == -1) {
            printf("point without pair: %d\n", id);
            single_points++;
        }
    }
    printf("Total different beacons: %zu\n", single_points + global_ids.size());

    // Assume 1st scanner position to (0, 0, 0)
    for (int current_scanner = 1; current_scanner <= scanner_id; current_scanner++) {



    }
//    Beacon b = points.begin()->second;
//    printf("Beacon: %s\n", b.str().c_str());
//    int id = 0;
//    for (auto& transformation: transformations) {
//        Beacon result_beacon = transformation(b);
//        printf("Transformation: %d => %s\n", id, result_beacon.str().c_str());
//        id++;
//    }
    for(const auto& num: intersects) {
        printf("Size: %zu: count %d\n", num.first, num.second);
    }

    ::printf("Task 2 result: %zu\n", result);
    return 0;
}

