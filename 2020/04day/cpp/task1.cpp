/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:i Day 4 Advent of Code 2020
 *
 *        Version:  0.1.0
 *        Created:  04.12.2020
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map>

using std::string;
using std::vector;

struct doc {
    std::map<string, string> data;
    int field_count;
    std::map<string, int> fields;
    bool valid;
};

doc create_doc(string line) {
    doc d {};
    std::stringstream record_line { line };
    bool cid_present = false;
    for (string field; getline(record_line, field, ' ');) {
        std::stringstream field_stream { field };
        string key, value;
        getline(field_stream, key, ':');
        getline(field_stream, value);
        d.fields[key]++;
        if (d.fields[key] == 1) {
            d.field_count++;
        }
        d.data[key] = value;
        if (key == "cid") {
            cid_present = true;
        }
        ::printf("%s -> %s ", key.c_str(), value.c_str());
    }
    ::printf("\n%d, %d\n", d.field_count, cid_present);
    if ((d.field_count == 8) or (d.field_count == 7 and (not cid_present))) {
        d.valid = true;
    } else {
        d.valid = false;
    }
    return d;
}

int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    std::vector<std::string> records {};
    records.reserve(260);
    string last = "";

    for (std::string line; getline(input, line);) {
        ::printf("Line: %zu %s\n", line.length(), line.c_str());
        if (line.size() == 0) {
            // Skip empty line
            records.push_back(last);
            last = "";
            continue;
        }
        if (last.size() > 0) {
            last = last + ' ' + line;
        } else {
            last = line;
        }
    }
    if (last != "") {
        records.push_back(last);
    }
    int valid_docs = 0;
    for (string record: records) {
        doc d = create_doc(record);
        printf("Record: %s -- %s\n", record.c_str(), d.valid ? "valid" : "invalid");
        if (d.valid) {
            valid_docs++;
        }
    }
    ::printf("Total: %zu\n", records.size());
    ::printf("Task 1: %d valid docs\n", valid_docs);
    return 0;
}
