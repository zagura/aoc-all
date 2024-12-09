/*
 * =====================================================================================
 *
 *       Filename:  task2.cpp
 *
 *    Description:  Advent of Code 2024 - Day 9
 *
 *        Version:  0.1.0
 *        Created:  09.12.2024
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <array>
#include <algorithm>
#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <print>

struct INode {
    INode(): id(0), len(0), block(false) {}
    int id;
    int len;
    bool block;
};

std::list<INode> unroll_files(const std::string& data){
    std::list<INode> fs {};
    bool file = true;
    int file_id = 0;
    for(const auto& c: data) {
        int digit = c - '0';
        INode node {};
        node.len = digit;
        node.block = file;
        if (file) {
            node.id = file_id;
        } else {
            node.id = 0;
        }
        fs.push_back(node);
        if (file) {
            file_id++;
        }
        file = not file;
    }
    return fs;
}
void print_fs(const std::list<INode>& fs) {
    for (auto& node: fs) {
        for (int i = 0; i < node.len; i++) {
            if (node.block) {
                std::print("{}", node.id);
            } else {
                std::print(".");
            }
        }
    }
    std::print("\n");
}

std::list<INode> compact_fs(std::list<INode> files) {
    for (auto iter = files.rbegin(); iter != files.rend(); iter++) {
        if (not iter->block) {
            continue;
        }
        // print_fs(files);
        for (auto front = files.begin(); front != files.end(); front++) {
            if (front->id == iter->id) {
                break;
            }
            // *iter fit size of empty slot
            if (not front->block && front->len >= iter->len) {
                front->len -= iter->len;
                INode n {};
                n.id = iter->id;
                n.block = true;
                n.len = iter->len;
                // iter->id = 0;
                iter->block = false;
                //auto new_iter =
                files.insert(front, n);
                break;
            }
        }
    }
    return files;
}

uint64_t checksum(const std::list<INode>& fs) {
    uint64_t chksum = 0;
    uint64_t index = 0;
    for (const auto &node: fs) {
        if (node.block) {
            for (int i = 0; i < node.len; i++) {
                chksum += (index * node.id);
                index ++;
            }
        }
        else {
            index += node.len;
        }
    }
    return chksum;
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
    std::string line;
    std::getline(input, line);
    auto fs = unroll_files(line);
    // print_fs(fs);
    auto compacted = compact_fs(fs);
    // print_fs(compacted);
    uint64_t total_sum = checksum(compacted);

    std::println("Task 1 result: {}", total_sum);
    return 0;
}

