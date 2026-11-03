/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  AoC 2015 - Day 11
 *                  --- Day 11: Corporate Policy ---
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

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::getline;
using std::stringstream;

using Pass = std::vector<int>;

static const std::map<char, int> alphabet {
    { 'a', 0 },
    { 'b', 1 },
    { 'c', 2 },
    { 'd', 3 },
    { 'e', 4 },
    { 'f', 5 },
    { 'g', 6 },
    { 'h', 7 },
    { 'j', 8 },
    { 'k', 9 },
    { 'm', 10 },
    { 'n', 11 },
    { 'p', 12 },
    { 'q', 13 },
    { 'r', 14 },
    { 's', 15 },
    { 't', 16 },
    { 'u', 17 },
    { 'v', 18 },
    { 'w', 19 },
    { 'x', 20 },
    { 'y', 21 },
    { 'z', 22 }
};

static const std::array<char, 23> translate {
    'a',
    'b',
    'c',
    'd',
    'e',
    'f',
    'g',
    'h',
    'j',
    'k',
    'm',
    'n',
    'p',
    'q',
    'r',
    's',
    't',
    'u',
    'v',
    'w',
    'x',
    'y',
    'z'
};

std::string pass2str(const Pass& pass) {
    std::string word;
    for (auto& p: pass) {
        word += translate.at(p);
    }
    return word;
}

Pass str2pass(const std::string& word) {
    Pass result {};
    for (const auto& c: word) {
        result.push_back(alphabet.at(c));
    }
    return result;
}

Pass next_pass(Pass pass) {
    for (auto it = pass.rbegin(); it != pass.rend(); it++) {
        if (*it == 22) {
            *it = 0;
        } else {
            *it += 1;
            break;
        }
    }
    return pass;
}

bool cond1(const Pass& pass) {
    int counter = 0;
    int last = 23;
    for (const auto& p: pass) {
        if (p == (last + 1)) {
            counter += 1;
        } else {
            if (counter >= 3) {
                return true;
            }
            counter = 1;
        }
        last = p;
    }
    return (counter >= 3);
}


bool cond3(const Pass& pass) {
    std::vector<int> pairs {};
    for (size_t i = 1; i < pass.size(); i++) {
        if (pass.at(i) == pass.at(i - 1)) {
            pairs.push_back(i);
        }
    }
    int last = -2;
    int count = 0;
    if (pairs.size() < 2) {
        return false;
    }
    for (const auto& p: pairs) {
        if (p - last >= 2) {
            count += 1;
        }
        last = p;
    }
    return (count >= 2);
}

Pass iterate_pass(Pass pass) {
    while (not cond1(pass) or not cond3(pass)) {
        pass = next_pass(pass);
    }
    return pass;
}
int main(int argc, char* argv[]) {
    std::ifstream input  { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }

    for (string line; getline(input, line);) {
        if (line.empty()) {
            continue;
        }
        Pass first = str2pass(line);
        Pass next = iterate_pass(first);
        printf("Next password: %s\n", pass2str(next).c_str());
    }
    int result = 0;
    ::printf("Task 1 result: %d\n", result);
    return 0;
}

