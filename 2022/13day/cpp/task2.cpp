/*
 * =====================================================================================
 *
 *       Filename:  task2.cpp
 *
 *    Description:  Advent of Code 2022 - Day 13
 *
 *        Version:  0.1.0
 *        Created:  14.12.2022
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
#include <list>
#include <map>
#include <vector>
#include <set>
#include <string_view>

using std::string;
using std::vector;
using std::array;
using std::map;
using std::stringstream;

//std::vector<std::string> tokenize(const std::string& data) {
//    std::vector<std::string> tokens;
//    std::stringstream token_stream { data };
//    for (std::string t; getline(token_stream, t, ','); ) {
//        tokens.push_back(t);
//    }
//    return tokens;
//}

//bool verify (const std::pair<std::string, std::string>& data) {
//    const auto left = tokenize(data.first);
//    const auto right = tokenize(data.second);

//    bool lower = false;
//    size_t ldown = 0, lup = 0;
//    size_t rdown = 0, rup = 0;
//    size_t llvl = 0, rlvl = 0;
//    int lval = 0, rval = 0;
//    for (size_t i = 0; i < std::min(left.size(), right.size()); i++) {
//        auto& l = left[i];
//        auto& r = rigth[i];
//        for (char c: l) {
//            if (c == '[') ldown++;
//            if (c == ']') lup++;
//        }
//        int ldigits = l.size() - ldown - lup;
//        for (char c: right[i]) {
//            if (c == '[') rdown++;
//            if (c == ']') rup++;
//        }
//        int rdigits = r.size() - rdown - rup;
//        if (ldigits > 0) {
//            lval = std::stoi(l.substr(ldown, digits));

//            ldown++;
//            lup++;
//        }
//        if (digits > 0) {
//            rval = std::stoi(r.substr(rdown, digits));
//            rdown++;
//            rup++;
//        }
//        if (ldigits && rdigits) {
//            if (lval < rval) {
//                return true;
//            } else if (lval > rval) {
//                return false;
//            }
//        }
//    }
//    return lower;
//}
// return:

// Assume w[0]
size_t find_close(const std::string& w) {
    size_t remain = 0;
    bool begin = false;
    for (size_t i = 0; i < w.size(); i++) {
        if (w.at(i) == '[') {
            remain++;
            begin = true;
        }
        if (begin && w.at(i) == ']') {
            remain--;
            if (remain == 0) {
                return i;
            }
        }
    }
    return std::string::npos;
}
std::string after_comma(std::string w) {
    if (w.find(',') == std::string::npos) {
        return "";
    } else {
        return w.substr(w.find_first_of(',') + 1);
    }
    return w;
}
// -1  -- substr in order
// 0   -- cannot verify
// 1   -- substr not in order
int verify(std::string l, std::string r) {
    if (l == "\n") {
        l.clear();
    }
    if (r == "\n") {
        r.clear();
    }
    auto l2 = l;
    auto r2 = r;
    if (l.empty() && r.empty()) {
        return 0;
    }
    if (l.empty()) return -1;
    if (r.empty()) return 1;
    if (l.front() == r.front() && l.front() == ',') return verify(l.substr(1), r.substr(1));
    if (l.front() == ',') return verify(l.substr(1), r);
    if (r.front() == ',') return verify(l, r.substr(1));
    if (r == l) return 0;
    if (l[0] == '[' && r[0] == '[') {
        //        l2 = l.substr(1, l.find_last_of(']') - 1);
        //        r2 = r.substr(1, r.find_last_of(']') - 1);
        l2 = l.substr(1, find_close(l) - 1);
        r2 = r.substr(1, find_close(r) - 1);
        int res = verify(l2, r2);
        if (res == 0) {
            //            return verify(l.substr(l.find_last_of(']') + 1), r.substr(r.find_last_of(']') + 1));
            return verify(l.substr(find_close(l) + 1), r.substr(find_close(r) + 1));
        } else {
            return res;
        }
    } else if (l.front() == '[' && r.front() != '[') {
        l2 = l.substr(1, find_close(l) - 1);
        if (r.front() == ']') return 1;
        int res = verify(l2, r2.substr(0, r2.find_first_of(',')));
        if (res != 0) return res;
        return verify(l.substr(find_close(l) + 1), after_comma(r));
        //        return res;
        //        return verify(l.substr(l.find_last_of(']') + 1), r.substr(1));
    } else if (l.front() != '[' && r.front() == '[') {
        if (l.front() == ']') return -1;
        ::printf(" l(%s), r(%s)\n", l.c_str(), r.c_str());
        r2 = r.substr(1, find_close(r) - 1);
        int res = verify(l2.substr(0, l2.find_first_of(',')), r2);
        //        return res;
        if (res != 0) return res;
        return verify(after_comma(l), r.substr(find_close(r) + 1));
        //        return verify(l.substr(1), r.substr(r.find_last_of(']') + 1));
    } else {
        int lnum = std::stoi(l.substr(0, l.find_first_of(',')));
        int rnum = std::stoi(r.substr(0, r.find_first_of(',')));
        if (lnum < rnum) return -1;
        if (lnum == rnum) {
            return verify(after_comma(l2), after_comma(r2));
        }
        if (lnum > rnum) return 1;
    }

    return 0;
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

    std::pair<std::string, std::string> current;
    int count = 0;
    std::vector<std::pair<std::string, std::string>> pairs;
    std::vector<std::string> packets;
    for (string line; getline(input, line);) {
        if (line.empty()) {
            count = 0;
            continue;
        }
        if (count == 1) {
            current.second = line;
            pairs.push_back(current);
            packets.push_back(current.first);
            packets.push_back(current.second);
            current = std::make_pair("", "");
            count = 0;
        } else if (count == 0) {
            current.first = line;
            count++;
        }
    }

    std::vector<std::pair<size_t, int>> ordered {};
    for (size_t i = 0; i < pairs.size(); i++) {
        ordered.push_back(std::make_pair(i + 1, verify(pairs[i].first, pairs[i].second)));
        ::printf("%s and %s -> %d\n", pairs[i].first.c_str(), pairs[i].second.c_str(), ordered.back().second);
    }
    size_t result = 0;
    for(auto [id, res]: ordered) {
        if (res == -1) {
            result += id;
        }
    }

    // Put divider packets
    std::set<std::string> divs = { "[[2]]", "[[6]]"};
    packets.push_back(std::string("[[2]]"));
    packets.push_back(std::string("[[6]]"));
    std::sort(packets.begin(), packets.end(), [](const std::string& l, const std::string& r) { return verify(l,r) == - 1; });
    size_t result2 = 1;
    for (size_t idx = 0; idx < packets.size(); idx++) {
        ::printf("%zu: %s\n", idx+1, packets[idx].c_str());
        if (divs.contains(packets[idx])) {
            result2 *= (idx + 1);
        }
    }


    ::printf("Task 1 result: %zu\n", result);
    ::printf("Task 2 result: %zu\n", result2);
    return 0;
}

