/*
 * =====================================================================================
 *
 *       Filename:  task2.cpp
 *
 *    Description:  Advent of Code 2020 - Day 13
 *
 *        Version:  0.1.0
 *        Created:  13.12.2020
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
#include <cstdint>

using std::string;
using std::vector;
using std::array;
using std::map;
using std::stringstream;
using std::pair;

using ull = unsigned long long int;
bool check_contest(const vector<pair<int, int>>& buses,
                   ull current_time) {
    for (const auto& [offset, id]: buses) {
        if ((current_time + offset) % id != 0) {
            return false;
        }
    }
    return true;
}

/// Buses: vector<pair<int, int>> of elements [offset, id]
ull get_time(const vector<pair<int, int>>& buses) {
    /// Stage 1: Prepare modulo values from vector
    vector<ull> modulos {};
    modulos.reserve(buses.size());
    for (const auto&[offset, id]: buses) {
        modulos.push_back(((buses.size() * id) - offset) % id);
    }
    /// Stage 2
    ull base = buses[0].second;
    ull rest = 0;

    for (size_t i = 1; i < modulos.size(); i++) {
        ull tmp_base = buses[i].second;
        ::printf("Modulos: [%zu] = %llu, buses[i] = { %d, %d }\n", i, modulos[i],
                 buses[i].first, buses[i].second);
        for (ull j = 0; j < tmp_base; j++) {
            ull mod = (base * j) + rest;
            if (mod % tmp_base == modulos[i]) {
                rest = mod;
                base *= tmp_base;
                break;
            }
        }
        ::printf("Base: %llu, rest: %llu\n", base, rest);
    }

    return rest;
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
    int result = 0;
    string line {};
    getline(input, line);
    int my_arrival = std::stoi(line);
    vector<int> bus_times {};
    vector<std::pair<int, int>> contest_buses {};
    int bus_order_no = 0;
    for(string t; getline(input, t, ','); bus_order_no++) {
        if ((not t.empty()) and t.front() != 'x') {
            bus_times.push_back(std::stoi(t));
            contest_buses.emplace_back(bus_order_no, std::stoi(t));
        }
    }
    std::sort(bus_times.begin(), bus_times.end());
    int minimum_departure_time = my_arrival + 2 * bus_times.back();
    int choosen_bus = 0;
    // Part 1
    for (auto& time: bus_times) {
        int departure_time = my_arrival;
        if (my_arrival % time != 0) {
            departure_time = departure_time + time - (my_arrival % time);
        }
        if (departure_time < minimum_departure_time) {
            minimum_departure_time = departure_time;
            choosen_bus = time;
        }
    }
    result = (minimum_departure_time - my_arrival) * choosen_bus;
    ::printf("Task 1 result: %d\n", result);
    // Part 2
    ::printf("Task 2 result: %llu\n", get_time(contest_buses));
    return 0;
}

