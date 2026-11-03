/*
 * =====================================================================================
 *
 *       Filename:  task2.cpp
 *
 *    Description:  AoC 2015 - Day 14
 *                  --- Day 14: Reindeer Olympics ---
 *
 *        Version:  1.0
 *        Created:  03.11.2026
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <string>
#include <fstream>
#include <array>
#include <map>
#include <set>
#include <climits>
#include <cinttypes>

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::getline;
using std::stringstream;

struct Reindeer {
    Reindeer(std::string n, int s, int rt, int rt2): name(n), speed(s), running_time(rt), rest_time(rt2) {}
    std::string name;
    uint64_t speed;
    uint64_t running_time;
    uint64_t rest_time;
    std::vector<uint64_t> distances;
};

uint64_t distance(Reindeer& r, uint64_t time) {
    if (time <= r.running_time) {
        return r.speed * time;
    }
    uint64_t dist = r.running_time * r.speed;
    if (time <= r.running_time + r.rest_time) {
        return dist;
    }
    return dist + distance(r, time - (r.running_time + r.rest_time));
}

int main(int argc, char* argv[]) {
    std::ifstream input  { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    uint64_t task_time = 2503;
    uint64_t result = 0;
    std::vector<Reindeer> rds {};
    for (string line; getline(input, line);) {
        if (line.empty()) {
            continue;
        }
        stringstream ss { line };
        std::vector<string> tokens {};
        for (string token; getline(ss, token, ' ');) {
            tokens.push_back(token);
        }
        int speed = std::stoi(tokens[3]);
        int running_time = std::stoi(tokens[6]);
        std::string name = tokens[0];
        int rest_time = std::stoi(tokens[tokens.size() - 2]);
        Reindeer r(name, speed, running_time, rest_time);
        rds.push_back(r);
        uint64_t dist = distance(r, task_time);
        for (uint64_t t = 0; t <= task_time; ++t) {
            rds.back().distances.push_back(distance(r, t));
        }
        ::printf("%s: %" PRIu64 "\n", r.name.c_str(), dist);
        if (dist > result) {
            result = dist;
        }
    }
    std::map<std::string, int> points {};
    for (const auto& r: rds) {
        points[r.name] = 0;
    }
    for (size_t t = 1; t < task_time; t++) {
        uint64_t max_dist = 0;
        for (const auto& r: rds) {
            if (r.distances[t] > max_dist) {
                max_dist = r.distances[t];
            }
        }
        for (const auto& r: rds) {
            if (r.distances[t] == max_dist) {
                points[r.name]++;
            }
        }
    }
    int lead_points = 0;
    for(const auto& [name, pts]: points) {
        if (pts > lead_points) {
            lead_points = pts;
        }
    }
    ::printf("Task 1 result: %" PRIu64 "\n", static_cast<uint64_t>(lead_points));
    return 0;
}