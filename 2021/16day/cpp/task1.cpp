/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2021 - Day 16
 *
 *        Version:  0.1.0
 *        Created:  16.12.2021
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <cstdio>
#include <cinttypes>
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

struct Register {
    std::vector<int> versions;
    std::vector<int> types;
    std::vector<int> values;
};

uint8_t decode_version(const std::vector<uint8_t>& data, size_t start_pos) {
    const auto bits = &(data[start_pos]);
    return (bits[0] << 2) + (bits[1] << 1) + bits[2];
}

uint8_t decode_type(const std::vector<uint8_t>& data, size_t start_pos) {
    const auto bits = &(data[start_pos]);
    return (bits[0] << 2) + (bits[1] << 1) + bits[2];
}

int decode_count(const std::vector<uint8_t>& data, size_t start_pos) {
    const auto bits = &(data[start_pos]);
    int count = 0;
    for(size_t i = 0; i < 11; i++) {
        count += (bits[i] << (10 - i));
    }
    return count;

}
int decode_length(const std::vector<uint8_t>& data, size_t start_pos) {
    const auto bits = &(data[start_pos]);
    int length = 0;
    for(size_t i = 0; i < 15; i++) {
        length += (bits[i] << (14 - i));
    }
    return length;
}

int literal_value(const std::vector<uint8_t>& data, Register& reg, size_t start_pos) {
    const auto bits = &(data[start_pos]);
    int i = 0;
    int number = 0;
    while (bits[i] == 1) {
        i++;
        for (int index = 0; index < 4; index++) {
            number <<= 1;
            number += bits[i + index];
        }
        i += 4;
    }
    // last hex symbol
    i++;
    for (int index = 0; index < 4; index++) {
        number <<= 1;
        number += bits[i + index];
    }
    i += 4;
    printf("Number: %d\n", number);
    reg.values.push_back(number);
    return i;
}


int try_decode(const std::vector<uint8_t>& data, Register& reg, size_t start_pos) {
    const auto bits = &(data[start_pos]);
    printf("Decode from %zu\n", start_pos);
    if (start_pos > data.size()) {
        throw std::runtime_error("Fail");
    }
    int len = 0;
    uint8_t version = decode_version(data, start_pos + len);
    reg.versions.push_back(version);
    len += 3;
    uint8_t packet_type = decode_type(data, start_pos + len);
    reg.types.push_back(packet_type);
    len += 3;
    if (packet_type != 4) {
        uint8_t type = bits[len];
        len++;
        if (type == 0) {
            int length = decode_length(data, start_pos + len);
            printf("Subpacket length: %d\n", length);
            len += 15;
            int inner_length = 0;
            while (inner_length < length) {
                inner_length += try_decode(data, reg, start_pos + len + inner_length);
            }
            len += inner_length;
        } else if (type == 1) {
            int count = decode_count(data, start_pos + len);
            printf("Subpacket count: %d\n", count);
            len += 11;
            int offset = 0;
            for (int i = 0; i < count; i++) {
                offset += try_decode(data, reg, start_pos + len + offset);
            }
            len += offset;
        }
    } else {
        len += literal_value(data, reg, start_pos + len);
    }
    return len;
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
    std::vector<uint8_t> bits {};
    bits.reserve(1024);
    for (string line; getline(input, line); ) {
        if (line.empty()) {
            continue;
        }
        for (auto& c: line) {
            uint8_t value = 0;
            if (c >= '0' && c <= '9') {
                value = c - '0';
            } else if (c >= 'A' && c <= 'F') {
                value = c - 'A' + 10;
            }
            bits.push_back((value & 0x8) >> 3);
            bits.push_back((value & 0x4) >> 2);
            bits.push_back((value & 0x2) >> 1);
            bits.push_back((value & 0x1) >> 0);
        }
    }
    Register reg;
    printf("Data size %zu\n", bits.size());
    try_decode(bits, reg, 0);
    size_t result = 0;
    for (auto& el: reg.versions) {
        result += el;
    }
    ::printf("Task 1 result: %zu\n", result);
    return 0;
}
