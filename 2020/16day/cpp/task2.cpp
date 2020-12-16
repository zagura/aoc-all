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
using std::array;
using std::map;
using std::stringstream;
using std::pair;

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

bool in_range(const Field& f, int val) {
        return (val >= f.l1 and val <= f.h1) or
               (val >= f.l2 and val <= f.h2);
}

bool ticket_invalid(const vector<int>& ticket, const vector<bool>& range) {
    for (const auto& t: ticket) {
        if (range.at(t) == false) {
            return true;
        }
    }
    return false;
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
    tickets.erase(std::remove_if(tickets.begin(), tickets.end(),
                                 [&range] (auto& t) { return ticket_invalid(t, range);}),
                                    tickets.end());
    std::map<string, int> fields_result {};
    std::vector<std::vector<string>> matched;
    matched.resize(tickets[0].size());
    for (const auto& of: order_fields) {
        const auto& f = fields.at(of);
        printf("Field: %s", of.c_str());
        for (size_t index = 0; index < tickets[0].size(); index++) {
            if (std::count_if(tickets.begin(), tickets.end(), [&f, &index](auto t){
                    return in_range(f, t[index]);}) == static_cast<int>(tickets.size())
                    and in_range(f, my_ticket[index])) {
                printf("%s - match at %zu\n", of.c_str(), index);
                //fields_result.emplace(of, index);
                matched[index].push_back(of);
            }
        }
    }

    while (fields_result.size() < order_fields.size()) {
        for (size_t i = 0; i < matched.size(); i++) {
            if (matched[i].size() == 1) {
                string name = matched[i].front();
                for (auto& match:matched) {
                    match.erase(std::remove_if(match.begin(), match.end(), [&name] (auto& s) { return name == s; }), match.end());
                }
                fields_result.emplace(name, i);
            }
        }
    }

    unsigned long long int result2 = 1;
    printf("fields result: %zu\n", fields_result.size());
    for (auto& f: fields_result) {
        ::printf("%s => %d : %d\n", f.first.c_str(), f.second, my_ticket[f.second]);
        if (f.first.starts_with("departure")) {
            printf("%s: %d\n", f.first.c_str(), my_ticket[f.second]);
            result2 *= static_cast<unsigned long long int>(my_ticket[f.second]);
        }
    }


/*  while (input >> dat) {
        arr.push_back(data);
    }
*/

    ::printf("Task 1 result: %d\n", result);
    ::printf("Task2 result %llu\n", result2);
    return 0;
}

