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
    bool operator==(const Beacon& other) {
        return other.x == x
            && other.y == y
            && other.z == z
            && other.scanner_id == scanner_id
            && other.line_no == line_no
            && other.global_id == global_id;
    }
    bool operator!=(const Beacon& other) {
        return !((*this) == other);
    }
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

void leave_most_frequent(std::vector<std::pair<Beacon, Beacon>>& beacons) {
    std::map<int, size_t> counts;
    /// Create frequency map scanner_id -> frequency
    for (const auto& [left, right]: beacons) {
        counts[left.scanner_id]++;
    }

    /// Get the most frequent element
    std::pair<int, size_t> max_count = *counts.begin();
    for (const auto& [scanner_id, count]: counts) {
        if (count > max_count.second) {
            max_count = std::make_pair(scanner_id, count);
        }
    }

    /// Remove other beacon pair
    std::erase_if(beacons, [&max_count](const auto& beacon_pair) {
        return beacon_pair.first.scanner_id != max_count.first;
    });
}
//template <typename T>
std::array<std::function<Beacon(Beacon)>, 48> transformations {{
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

    { [](Beacon b) noexcept { return Beacon::rotate(b); }},
    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::move_right(b)); }},
    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::move_right(Beacon::move_right(b))); }},

    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::mirror_x(b)); }},
    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::mirror_y(b)); }},
    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::mirror_z(b)); }},
    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::mirror_x(Beacon::mirror_y(Beacon::mirror_z((b))))); }},
    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::mirror_x(Beacon::mirror_y(b))); }},
    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::mirror_x(Beacon::mirror_z(b))); }},
    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::mirror_y(Beacon::mirror_z(b))); }},

    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::move_right(Beacon::mirror_x(b))); }},
    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::move_right(Beacon::mirror_y(b))); }},
    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::move_right(Beacon::mirror_z(b))); }},
    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::move_right(Beacon::mirror_x(Beacon::mirror_y(Beacon::mirror_z((b)))))); }},
    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::move_right(Beacon::mirror_x(Beacon::mirror_y(b)))); }},
    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::move_right(Beacon::mirror_x(Beacon::mirror_z(b)))); }},
    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::move_right(Beacon::mirror_y(Beacon::mirror_z(b)))); }},

    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::move_right(Beacon::move_right(Beacon::mirror_x(b)))); }},
    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::move_right(Beacon::move_right(Beacon::mirror_y(b)))); }},
    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::move_right(Beacon::move_right(Beacon::mirror_z(b)))); }},
    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::move_right(Beacon::move_right(Beacon::mirror_x(Beacon::mirror_y(Beacon::mirror_z((b))))))); }},
    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::move_right(Beacon::move_right(Beacon::mirror_x(Beacon::mirror_y(b))))); }},
    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::move_right(Beacon::move_right(Beacon::mirror_x(Beacon::mirror_z(b))))); }},
    { [](Beacon b) noexcept { return Beacon::rotate(Beacon::move_right(Beacon::move_right(Beacon::mirror_y(Beacon::mirror_z(b))))); }},

}};

size_t m_dist(const Beacon& b1, const Beacon& b2) {
    return abs(b1.x - b2.x) + abs(b1.y - b2.y) + abs(b1.z - b2.z);
}

bool is_transfrom_correct(std::vector<std::pair<Beacon, Beacon>>& transformed) {
    bool correct_transform = true;
    for (auto& [p1, b1]: transformed) {
        for (auto& [p2, b2]: transformed) {
            if (b1 != b2 && p1.scanner_id == p2.scanner_id) {
                if (((p2.x - p1.x) != (b2.x - b1.x))
                    || ((p2.y - p1.y) != (b2.y - b1.y))
                    || ((p2.z - p1.z) != (b2.z - b1.z))) {
//                    printf("Fail on points (%s,%s) -> (%s,%s)\n", p1.str().c_str(), p2.str().c_str(), b1.str().c_str(), b2.str().c_str());
                    return false;
                }
            }
        }
    }
    return correct_transform;
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
    std::map<std::size_t, std::set<int>> global_ids {};
    for (auto& n1: neighbors) {
        for (auto& n2: neighbors) {
            if (n1.first != n2.first) {
                if (points[n1.first].scanner_id == points[n2.first].scanner_id) {
                    continue;
                }
                std::vector<int> intersect {};
                std::set_intersection(n1.second.begin(), n1.second.end(),
                                      n2.second.begin(), n2.second.end(),
                                      std::back_inserter(intersect));
                if (intersect.size() > 3) {
                    /// For intersect.size() == 1, there would be two ends
                    /// of the same section
                    intersects[intersect.size()]++;
                    printf("Common points: %d (%d) [%d] and %d (%d) [%d]: %zu\n", n1.first,
                           points[n1.first].scanner_id , points[n1.first].global_id, n2.first,
                           points[n2.first].scanner_id, points[n2.first].global_id, intersect.size());
                // Assign global beacon id to both beacons
                    int gid = points[n1.first].global_id;
                    int gid2 = points[n2.first].global_id;
                    if (gid2 != -1 && gid2 != gid) {
                        printf("[WARN] Global Id missmatch: %d vs %d\n", gid, gid2);
                        if (gid == -1) {
                            points[n1.first].global_id = gid2;
                            gid = points[n1.first].global_id;
                            global_ids[gid2].insert(n1.first);
                        } else {
                            /// Merge two gid sets into one
                            for (auto& id: global_ids[gid2]) {
                                global_ids[gid].insert(id);
                                points[id].global_id = gid;
                            }
                            global_ids[gid2].clear();
                            global_ids.erase(global_ids.find(gid2));
                        }
                    }
                    if (gid == -1) {
                        gid = global_ids.size();
                        points[n1.first].global_id = gid;
                        global_ids[gid].insert(n1.first);
                    }
                    if (points[n2.first].global_id == -1) {
                        points[n2.first].global_id = gid;
                        global_ids[gid].insert(n2.first);
                    }
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
        printf("Global id %zu:", gid_set.first);
        for (auto& el: gid_set.second) {
            printf(" %d", el);
        }
        printf("\n");
    }
//    size_t single_points = 0;
//    for (auto& [id, point]: points) {
//        if (point.global_id == -1) {
//            printf("point without pair: %d\n", id);
//            single_points++;
//        }
//    }
//    printf("Total different beacons: %zu\n", single_points + global_ids.size());

    // Assume 1st scanner position to (0, 0, 0)
    std::vector<bool> scanner_passes (scanner_id, false);
    std::map<int, Beacon> scanner_positions {};
    scanner_positions.emplace(0, Beacon(0, 0, 0));
    scanner_passes[0] = true;
    std::map<size_t, size_t> vector_sizes{};
    bool pass_change = true;
    while(pass_change) {
        pass_change = false;
        for (int current_scanner = 1; current_scanner <= scanner_id; current_scanner++) {
            if (scanner_passes[current_scanner]) {
                continue;
                // Skip processed scanners
            }

            std::vector<std::pair<Beacon, Beacon>> matched_beacons{};
            // Get all points for given scanner_id (current_scanner)
            for (const auto& gid_set: global_ids) {
                int point_id = -1;
                for (const auto& id: gid_set.second) {
                    if (points[id].scanner_id == current_scanner) {
                        // Current scanner "scanned" beacon with this global_id
                        point_id = id;
                        break;
                    }
                }
                if (point_id != -1) {
                    for (const auto& id: gid_set.second) {
                        if (scanner_passes[points[id].scanner_id]) {
                            matched_beacons.emplace_back(points[id], points[point_id]);
                        }
                    }
                }
            }
            leave_most_frequent(matched_beacons);
            printf("Verifying scanner: %d (%zu)\n", current_scanner, matched_beacons.size());
            if (matched_beacons.size() < 12) {
                continue;
            }

            printf("Found to change: %d - size %zu\n", current_scanner, matched_beacons.size());

            vector_sizes[matched_beacons.size()]++;
            /// Here, we assume that all previous scanners have already fixed orientation
            /// Try to match correct transformation and verify through diffs between points
//            size_t tid = 0;
            for (const auto& transform: transformations) {
                std::vector<std::pair<Beacon, Beacon>> transformed {};
                for (auto& beacon_pair: matched_beacons) {
                    transformed.emplace_back(beacon_pair.first, transform(beacon_pair.second));
                }
                if (is_transfrom_correct(transformed)){
                    printf("Correct transform for scanner %d\n", current_scanner);
                    scanner_passes[current_scanner] = true;
                    int last_correct_scanner_id = matched_beacons.begin()->first.scanner_id;
                    Beacon last_position = scanner_positions.at(last_correct_scanner_id);
                    Beacon diff_start = matched_beacons.begin()->first;
                    Beacon diff_end = transform(matched_beacons.begin()->second);
                    diff_end = Beacon::mirror_x(Beacon::mirror_y(Beacon::mirror_z(diff_end)));
                    diff_start.translate(diff_end);
                    printf("%s - %s = %s", matched_beacons.begin()->first.str().c_str(), matched_beacons.begin()->second.str().c_str(),
                           diff_start.str().c_str());
                    last_position.translate(diff_start);
                    scanner_positions.emplace(current_scanner, last_position);
                    for (auto& [id, p]: points) {
                        if (p.scanner_id == current_scanner) {
                            auto p2 = transform(p);
                            p = p2;
                            p2.translate(diff_start);
                            printf("After: %s\n", p2.str().c_str());
                        }
                    }
                    scanner_passes[current_scanner] = true;
                    pass_change = true;
                    break;
                }
            }
        }
    }
    size_t vec_sum = 0;
    for(const auto& [vec_size, count]: vector_sizes) {
        printf("Vector size: (%zu), count (%zu)\n", vec_size, count);
        vec_sum += count;
    }
    printf("vector_sizes %zu sum %zu\n", vector_sizes.size(), vec_sum);

//    Beacon b = points.begin()->second;
//    printf("Beacon: %s\n", b.str().c_str());
//    int id = 0;
//    for (auto& transformation: transformations) {
//        Beacon result_beacon = transformation(b);
//        printf("Transformation: %d => %s\n", id, result_beacon.str().c_str());
//        id++;
//    }
//    for(const auto& num: intersects) {
//        printf("Size: %zu: count %d\n", num.first, num.second);
//    }

    size_t max_dist = 0;
    for (auto& [id, pos]: scanner_positions) {
        for (auto& [id2, pos2]: scanner_positions) {
            if (id < id2) {
                size_t current_dist = m_dist(pos, pos2);
                if (current_dist > max_dist) {
                    max_dist = current_dist;
                }
            }
        }
        printf("Transformed scanner id: %d position %s\n", id, pos.str().c_str());
    }
    result = max_dist;
    ::printf("Task 2 result: %zu\n", result);
    return 0;
}

