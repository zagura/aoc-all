/*
 * =====================================================================================
 *
 *       Filename:  task2.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01.12.2021 19:05
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */


#include <iostream>
#include <fstream>
#include <sstream>
#include <string_view>
#include <vector>
#include <cinttypes>
#include <fmt/format.h>
#include <map>

int main() {
    constexpr size_t kDataSize = 2000;
    std::ifstream input {"input.in"};
    std::vector<int> data;
    data.reserve(kDataSize);
    int number = 0;
    if (not input.good()) {
        std::cerr << "Cannot open file";
        return -2;
    }
    while(input >> number) {
        data.push_back(number);
    }
    int sliding_window = data[0] + data[1] + data[2];
    int increase_count = 0;
    /// It actually is enough to compare data[i] and data[i - 3], as
    /// data[i - 1] + data[i - 2] is common to both sum expressions
    for (size_t i = 3; i < data.size(); i++) {
        int new_window = sliding_window + data[i] - data[i - 3];
        if (new_window > sliding_window) {
            increase_count++;
        }
        sliding_window = new_window;
    }
    std::cout << increase_count << std::endl;
    return 0;
}
