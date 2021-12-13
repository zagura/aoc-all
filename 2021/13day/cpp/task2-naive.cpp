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

ull find_next(int next_offset, int id, ull loop) {

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
    auto offset = std::find_if(contest_buses.begin(), contest_buses.end(),
                               [a = bus_times.back()](auto el){ return el.second == a;})->first;
    ::printf("Offset: %d: %d\n", bus_times.back(), offset);
    unsigned long long int current_time =  bus_times.back() - offset;
    long int iter = 0;
    while(not check_contest(contest_buses, current_time)) {
        current_time += bus_times.back();
//        if (current_time > 1068700) {
//            ::printf("Current time: %llu\n", current_time);
//        }
//        if (current_time > 1068800) {
//            break;
//        }
        iter++;
    }
    ::printf("Task 2 result: %llu at iter %ld \n", current_time, iter);
    return 0;
}

