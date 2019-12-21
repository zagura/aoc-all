/*
 * =============================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Day 16 - Flawed Frequency Transmission
 *
 *        Version:  1.0
 *        Created:  19.12.2019
 *
 *         Author:  Michał Zagórski (zagura), <mzagorsk@student.agh.edu.pl>
 *   Organization:  AGH University of Science and Technology, Kraków
 *
 * =============================================================================
 */
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <array>
#include <algorithm>
#include <iomanip>

using namespace std;
const size_t kPatternSize = 4;
const array<int, kPatternSize> base_pattern =  { 0, 1, 0, -1 };

int char2int(char c) {
    int c_as_i = static_cast<int>(c);
    int zero_as_i = static_cast<int>('0');
    return c_as_i - zero_as_i;
}

int abs(int a) {
    if (a < 0) {
        a *= -1;
    }
    return a;
}


int get_index_in_pattern(size_t target_index, size_t pattern_index) {
    size_t base_size = kPatternSize * (target_index + 1);
    size_t index = pattern_index % base_size;
    return ((index + 1) / (target_index + 1)) % kPatternSize;
}

void single_phase (vector<int>& input) {
    for (size_t index = 0; index < input.size(); index++) {
        int current = 0;
        for (size_t i = index; i < input.size(); i++) {
            int pattern = base_pattern.at(get_index_in_pattern(index, i));
            current += (pattern * input[i]);
            current %= 100000000;
        }
        input[index] = abs(current % 10);
    }
}

void print_numbers(const vector<int> n) {
    for (auto& e: n) {
        cout << e;
    }
    cout << endl;
}

void print8(const vector<int> v) {
    for (int i = 0; i < 8; i++) {
        cout << v[i];
    }
    cout << endl;
}

int main() {
    string line;
    vector<int> numbers;
    getline(std::cin, line);
    for (char c: line) {
        int n = char2int(c);
        numbers.push_back(n);
    }
    print_numbers(numbers);
    for (int i = 0; i < 100; i++) {
        single_phase(numbers);
//        print_numbers(numbers);
    }
    print8(numbers);
    return 0;
}
