/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01.12.2021 19:01
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
    constexpr size_t kDataSize = 200;
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
    int previous = data[0];
    int increase_count = 0;
    for (int n1: data) {
        if (n1 > previous) {
            increase_count++;
        }
        previous = n1;
    }
    std::cout << increase_count << std::endl;
    return 0;
}
