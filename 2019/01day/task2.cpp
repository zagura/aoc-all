/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05.12.2019 18:48:28
 *
 *         Author:  Michał Zagórski (zagura), <mzagorsk@student.agh.edu.pl>
 *   Organization:  AGH University of Science and Technology, Kraków
 *
 * =====================================================================================
 */
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::getline;
using std::stringstream;

int fuel_formula(int mass) {
    int fuel = mass / 3;
    return fuel - 2;
}

int formula2(int fuel) {
    int next_fuel = fuel_formula(fuel);
    while (next_fuel > 0) {
        fuel += next_fuel;
        next_fuel = fuel_formula(next_fuel);
    }
    return fuel;
}

int main () {
    vector <int> masses;
    masses.reserve(200);
    for (string line; getline(cin, line); ) {
        if (line == "\n") {
            continue;
        }
        stringstream ss { line };
        int mass;
        ss >> mass;
        masses.push_back(mass);
    }
    int total_fuel = 0;
    for (auto& mass: masses) {
        total_fuel += formula2(fuel_formula(mass));
    }
    cout << total_fuel << endl;
    return 0;
}
