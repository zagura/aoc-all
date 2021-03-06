/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
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

using std::string;
using std::vector;
using std::array;
using std::map;
using std::stringstream;



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
    for(string t; getline(input, t, ','); ) {
        if ((not t.empty()) and t.front() != 'x') {
            bus_times.push_back(std::stoi(t));
        }
    }
    std::sort(bus_times.begin(), bus_times.end());
    int minimum_departure_time = my_arrival + 2 * bus_times.back();
    int choosen_bus = 0;
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
    return 0;
}

