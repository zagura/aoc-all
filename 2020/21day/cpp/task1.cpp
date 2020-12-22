/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
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
        printf("%zu %zu\n", ingredients.back().size(),
               allergens.back().size());
    }

    result = std::count_if(ingredient_map.begin(), ingredient_map.end(),
                           [](auto& vec) { return vec.second.size() < 8; });

    int sum = 0;
    for (auto& a: allergens) {
        sum += a.size();
    }

    for (auto& el: allergen_map) {
        printf("Allergen (%s) count %zu\n", el.first.c_str(), el.second.size());
    }
    vector<size_t> ingredient_count_list;
    for (auto& el: ingredient_map) {
        ingredient_count_list.push_back(el.second.size());
    }
    size_t total_count = 0;
    std::sort(ingredient_count_list.begin(), ingredient_count_list.end());
    for (auto& i: ingredient_count_list) {
        if (i < 30) {
            total_count += i;
        }
        printf("Count: %zu\n", i);
    }
    printf("Total allergens: %d, %zu\n", sum, allergen_map.size());
    result = total_count;



    ::printf("Task 1 result: %d\n", result);
    return 0;
}

