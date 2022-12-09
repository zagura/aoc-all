/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2022 - Day 7
 *
 *        Version:  0.1.0
 *        Created:  07.12.2022
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <fstream>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <queue>

struct FileNode {
    std::string name;
    size_t size;
    std::vector<std::shared_ptr<FileNode>> children;
    const std::shared_ptr<FileNode> parent;

    FileNode(const std::string& n, std::shared_ptr<FileNode> p) : name(n), size(0), parent(p) {}
    std::shared_ptr<FileNode> find_child(std::string& n) {
        auto it = std::find_if(children.begin(), children.end(), [&n] (const auto& node) {
                                return node->name == n; });
        if (it != children.end()) {
            return *it;
        }
        return std::shared_ptr<FileNode>();
    }
    void count() {
        size_t s = 0;
        for (const auto& c: children) {
            s += c->size;
        }
        size = s;
    }
};

void process_list(std::stringstream& lines, std::shared_ptr<FileNode>& current) {
    std::string line;
    while (getline(lines, line)) {
        std::stringstream line_stream { line };
        if (line.substr(0, 3) == "dir") {
            std::string l, dirname;
            line_stream >> l >> dirname;
            current->children.push_back(std::make_shared<FileNode>(dirname, current));
        } else {
            std::string name;
            size_t size;
            line_stream >> size >> name;
            std::shared_ptr<FileNode> file = std::make_shared<FileNode>(name, current);
            file->size = size;
            current->children.push_back(file);
        }
    }

}

constexpr size_t task_size = 100000;

int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    if (!input.good()) {
        ::fprintf(stderr, "Cannot open input file\n");
        return 2;
    }
    std::string el;
    std::vector<std::string> cwd;
    size_t total_size = 0;
    std::shared_ptr<FileNode> root = std::make_shared<FileNode>(std::string("/"), (nullptr));
    std::shared_ptr<FileNode> current = root;
    while(getline(input, el, '$')) {
        ::printf("El: (%s)\n", el.c_str());
        if (el.empty()) {
            continue;
        }
        std::string cmd;
        std::stringstream cmd_stream { el };
        getline(cmd_stream, cmd);
        if (cmd.substr(1) == "ls") {
            process_list(cmd_stream, current);
        } else if (cmd.substr(1, 2) == "cd") {
            std::string arg = cmd.substr(cmd.find_last_of(' ') + 1);
            printf("cmd(%s), arg(%s)\n", cmd.c_str(), arg.c_str());
            if (arg == "..") {
                cwd.pop_back();
                current->count();
                if (current->size < task_size) {
                    total_size += current->size;
                }
                current = current->parent;
            } else {
                if (arg == "/") {
                    continue;
                }
                cwd.push_back(arg);
                current = current->find_child(arg);
            }
        }
    }

    ::printf("Task 1 result: %zu\n", total_size);
    return 0;
}
