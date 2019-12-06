/*
 * =====================================================================================
 *
 *       Filename:  sol.cc
 *
 *    Description:  Advent of code 2017, Day 1
 *
 *        Version:  1.0
 *        Created:  17.12.2017 13:06:37
 *
 *         Author:  Michał Zagórski (zagura), <mzagorsk@student.agh.edu.pl>
 *
 * =====================================================================================
 */

#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;


int main() {
    char c;
    unsigned long long int sum = 0;
    vector<unsigned> list;
    list.reserve(10000);
    while(cin>>c) {
        list.push_back(static_cast<unsigned> (c - '0'));
    }
    
    for(unsigned int i = 0; i < list.size(); i++) {
        if(list[(i+1) % list.size()] == list[i])
            sum += list[i];
    }
    cout << sum << endl;
    return 0;
}

