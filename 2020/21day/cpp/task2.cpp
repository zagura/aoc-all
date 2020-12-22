/*
 * =====================================================================================
 *
 *       Filename:  task2.cpp
 *
 *    Description:  Advent of Code 2020 - Day 21
 *
 *        Version:  0.1.0
 *        Created:  21.12.2020
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
#include <list>

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

    vector<vector<string>> ingredients;
    vector<vector<string>> allergens;
    std::map<string, vector<int>> ingredient_map;
    std::map<string, vector<int>> allergen_map;
    int line_no = 0;
    for (string line; getline(input, line); line_no++) {
        stringstream line_stream { line };
        string ingredient_list;
        string allergen_list;
        getline(line_stream, ingredient_list, '(');
        getline(line_stream, allergen_list, ')');
        stringstream ingredient_stream { ingredient_list };
        stringstream allergen_stream { allergen_list };
        vector<string> list;
        string token;
        while (ingredient_stream >> token) {
            list.push_back(token);
            ingredient_map[token].push_back(line_no);
        }
        ingredients.push_back(list);
        list.clear();
        allergen_stream >> token; /// Ignore "contains" at the beginning
        while (allergen_stream >> token) {
            if (token.back() == ',') {
                token.pop_back();
            }
            list.push_back(token);
            allergen_map[token].push_back(line_no);
        }
        allergens.push_back(list);
    }

    for (auto& ingredient: ingredient_map) {
        if (ingredient.second.size() < 30) {
            for (auto& list: ingredients) {
                std::erase_if(list, [&ingredient](string s) {return s == ingredient.first;});
            }
        }
    }
    for (auto it = ingredient_map.begin(); it != ingredient_map.end();) {
        if (it->second.size() < 30) {
            it = ingredient_map.erase(it);
        } else {
            ++it;
        }
    }

    map<string, string> allergen_match {};
    vector<std::pair<string, int>> ordered_allergens {};
    std::list<string> ingredient_list {};
    for (auto& el: ingredient_map) {
        ingredient_list.push_back(el.first);
    }
    for (auto& el: allergen_map) {
        ordered_allergens.emplace_back(el.first, el.second.size());
    }
    std::sort(ordered_allergens.begin(), ordered_allergens.end(), [](auto& l, auto& r) {
        return l.second > r.second;});

    while (allergen_match.size() < ordered_allergens.size()) {
    for (auto& a: ordered_allergens) {
        const vector<int>& lines = allergen_map.at(a.first);
        std::list<string> left = ingredient_list;
        for (const int line_no: lines) {
            auto& ilist = ingredients[line_no];
            for (auto it = left.begin(); it != left.end();) {
                /// Remove ingredient, which wasn't found in line, where given allergen exists
                if (std::find(ilist.begin(), ilist.end(), *it) == ilist.end()) {
                    it = left.erase(it);
                } else {
                    ++it;
                }
            }
        }
        if (left.size() != 1) {
            printf("Some error: %zu\n", left.size());
            for (auto& s: left) {
                printf("%s ", s.c_str());
            }
            printf("\n");
        } else {
            string found = left.front();
            printf("Found: %s\n", found.c_str());
            allergen_match.emplace(a.first, left.front());
            ingredient_list.remove_if([&found] (string s) { return found == s;});
            printf("Ingredient lists size: %zu\n", ingredient_list.size());
        }
    }
    }
    for (auto& f: allergen_match) {
        printf("%s,", f.second.c_str());
    }
    ::printf("Task 1 result: %d\n", result);
    return 0;
}

