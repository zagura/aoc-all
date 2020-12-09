/*
 * =====================================================================================
 *
 *       Filename:  task2.cpp
 *
 *    Description:  Advent of Code 2020 - Day 9
 *
 *        Version:  0.1.0
 *        Created:  09.12.2020
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
#include <queue>
#include <list>

bool verify(const std::vector<int>& numbers, int number) {
    // size - 1 - element with number
    size_t last_index = numbers.size() - 2;
    for (int i = 0; i < 24; i++) {
        for (int j = i + 1; j < 25; j++) {
            if (numbers.at(last_index - i) + numbers.at(last_index - j) == number) {
                return true;
            }
        }
    }
    return false;
}

std::pair<bool, int> find_sum(const std::vector<int>& numbers, int number, int begin, int end) {
    std::pair<bool, int> result {};
    result.first = false;
    int sum = numbers[begin];
    int lowest = sum;
    int highest = sum;
    for (int i = begin + 1; i < end; i++) {
        if (sum > number) {
            break;
        } else if (sum == number) {
            result.first = true;
            result.second = lowest + highest;
            return result;
        } else {
            sum += numbers[i];
            if (numbers[i] > highest) {
                highest = numbers[i];
            }
            if (numbers[i] < lowest) {
                lowest = numbers[i];
            }
        }

    }
    return result;
}

int get_sum(const std::vector<int>& numbers, int number, int index) {
    for (int i = 0; i < index - 1; i++) {
        auto [found, value] = find_sum(numbers, number, i, index);
        if (found) {
            return value;
        }
    }
    for (int i = 0; i < numbers.size() - index; i++) {
        auto [found, value] = find_sum(numbers, number, index + i, numbers.size() - 1);
        if (found) {
            return value;
        }
    }
    return -1;
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
    int result = 0;
    int number {};
    std::vector<int> numbers {};
    int invalid {};
    int invalid_index {};
    numbers.reserve(1000);
    while (input >> number) {
        numbers.push_back(number);
        if (numbers.size() > 25) {
            bool valid = verify(numbers, number);
            if (not valid) {
                invalid_index = numbers.size() - 1;
                invalid = number;
            }
        }
    }

//    for (int i
    ::printf("Task 1 result: %d\n", invalid);

    ::printf("Task 2 result: %d\n", get_sum(numbers, invalid, invalid_index));
    return 0;
}

