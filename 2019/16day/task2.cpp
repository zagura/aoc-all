/*
 * =============================================================================
 *
 *       Filename:  task2.cpp
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
const size_t kRepeat = 10000;
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
    long long int current = 0;
    for (auto& e: input) {
        current += e;
    }
    long long int next = current;
    for (size_t index = 0; index < input.size(); index++) {
        next -= input[index];
        input[index] = abs(current % 10);
        current = next;
    }
}

void print_numbers(const vector<int> n) {
    for (auto& e: n) {
        cout << e;
    }
    cout << endl;
}

void print8(const vector<int> v, size_t offset) {
    for (int i = offset; i < 8; i++) {
        cout << v[i];
    }
    cout << endl;
}

size_t get_offset(const vector<int> v) {
    size_t offset = 0;
    size_t base = 1;
    for (int i = 6; i >= 0; i--) {
        offset += (base * v[i]);
        base *= 10;
    }
    return offset;
}

int main() {
    string line;
    vector<int> numbers;
    getline(std::cin, line);
    for (char c: line) {
        int n = char2int(c);
        numbers.push_back(n);
    }
    vector<int> original_input = numbers;
    size_t offset = get_offset(original_input);
    numbers.reserve(kRepeat * numbers.size());
    for (size_t i = 0; i < kRepeat - 1; i++) {
        for (auto& n: original_input) {
            numbers.push_back(n);
        }
    }
    vector<int> numbers2;
    numbers2.reserve(numbers.size() - offset + 1);
    for (size_t i = offset; i < numbers.size(); i++) {
        numbers2.push_back(numbers.at(i));
    }
    numbers.clear();
//    print_numbers(numbers2);
    for (int i = 0; i < 100; i++) {
        single_phase(numbers2);
//        print_numbers(numbers);
    }

    print8(numbers2, 0);
    return 0;
}
