/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  01.12.2020 11:32:16
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
    std::cout << std::endl;
    std::pair<bool, bool> found { false, false };
    for (int n1: data) {
        for (int n2: data) {
            /* Condition from task 1 */
            if (n1 + n2 == 2020) {
                std::cout << fmt::format("n1: {} , n2: {} \n\t mul: {}", n1, n2, n1 * n2)
                          << std::endl;
                found.first = true;
            } else {
                /* Task 2: Third loop */
                for (int n3 : data) {
                    if (n1 + n2 + n3 == 2020) {
                        std::cout << fmt::format("n1: {}, n2: {}, n3 {} \n\t mul {}",
                                                 n1, n2, n3, n1 * n2 * n3)
                                  << std::endl;
                    }
                }
                found.second = true;
            }
        }
        if (found.first && found.second) {
//            break;
        }
    }
    return 0;
}
