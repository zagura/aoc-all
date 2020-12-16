/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2020 - Day 16
 *
 *        Version:  0.1.0
 *        Created:  16.12.2020
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <cstdio>
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
using std::map;
using std::stringstream;

struct Field {
    int l1;
    int h1;
    int l2;
    int h2;
};

void add_field(map<string, Field>& fields, string line, vector<bool>& range) {
    stringstream line_stream { line };
//    string token;
    string field_name;
    field_name.resize(100);
    int range1_low = 0, range1_high = 0;
    int range2_low = 0, range2_high = 0;
    getline(line_stream, field_name, ':');
    line = line.substr(field_name.size() + 2);
    sscanf(line.c_str(), "%d-%d or %d-%d",
           &range1_low, &range1_high, &range2_low, &range2_high);
    fields.emplace(field_name, Field{range1_low, range1_high, range2_low, range2_high});
    printf("Line: %s => %s,%d,%d,%d,%d\n", line.c_str(), field_name.c_str(), range1_low,
           range1_high, range2_low, range2_high);
    for (int i = range1_low; i <= range1_high; i++) {
        range[i] = true;
    }
    for (int i = range2_low; i <= range2_high; i++) {
        range[i] = true;
    }
}

vector<int> get_ticket(stringstream& ticket) {
    vector<int> ticket_vals {};
    ticket_vals.reserve(20);
    for (string val; std::getline(ticket, val, ','); ) {
        ticket_vals.push_back(std::stoi(val));
    }

    return ticket_vals;
}

int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    vector<bool> range {};
    range.resize(1000);
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    if (!input.good()) {
        ::fprintf(stderr, "Cannot open input file\n");
        return 2;
    }
    int result = 0;
    int read_state = 0;
    map<string, Field> fields {};
    vector<int> my_ticket {};
    vector<vector<int>> tickets {};
    std::vector<string> order_fields {};
    tickets.reserve(100);
    for (string line; getline(input, line); ) {
        if (line.empty()) {
            read_state++;
            continue;
        }
        stringstream internal;
        string ticket;
        switch(read_state) {
            case 0:
                add_field(fields, line, range);
                order_fields.push_back(line.substr(0, line.find(':')));
                break;
            case 1:
                getline(input, ticket);
                internal  = stringstream{ticket};
                my_ticket = get_ticket(internal);
                break;
            case 2:
                for (; getline(input, ticket); ) {
                    internal = stringstream { ticket };
                    tickets.push_back(get_ticket(internal));
                }
        }
    }
    // part1
    for (auto& t: tickets) {
        for (auto& f: t) {
            if (range[f] == false) {
//                printf("Field: %d\n", f);
                result += f;
            }
        }
    }

    ::printf("Task 1 result: %d\n", result);
    return 0;
}

