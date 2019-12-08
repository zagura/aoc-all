/*
 * =====================================================================================
 *
 *       Filename:  template.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08.12.2019 12:44:10
 *
 *         Author:  Michał Zagórski (zagura), <mzagorsk@student.agh.edu.pl>
 *   Organization:  AGH University of Science and Technology, Kraków
 *
 * =====================================================================================
 */
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <exception>

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::getline;
using std::stringstream;


size_t get_ribbon(vector<int>& dims) {
    if (dims.size() < 3) {
        throw std::runtime_error("Invalid dims size");
    }
    size_t s1 = dims[0] * dims[1];
    size_t sum1 = dims[0] + dims[1];
    size_t smallest = s1;
    size_t smallest_sum = sum1;
    size_t s2 = dims[1] * dims[2];
    size_t sum2 = dims[1] + dims[2];
    if (smallest > s2) {
        smallest = s2;
        smallest_sum = sum2;
    }
    size_t sum3 = dims[0] + dims[2];
    size_t s3 = dims[0] * dims[2];
    if (smallest > s3) {
        smallest_sum = sum3;
    }
    return 2*smallest_sum + (dims[0] * dims[1] * dims[2]);
}

int main() {
    string line;
    size_t total_ribbon = 0;
    while(getline(std::cin, line)) {
        stringstream ss { line };
        vector<int> dims;
        string dim; 
        while(getline(ss, dim, 'x')) {
            dims.push_back(std::stoi(dim));
        }
        total_ribbon += get_ribbon(dims);

    }
    cout << "Task 2 solution: " << total_ribbon << endl;
    return 0;
}

