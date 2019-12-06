/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04.12.2019 20:53:35
 *
 *         Author:  Michał Zagórski (zagura), <mzagorsk@student.agh.edu.pl>
 *   Organization:  AGH University of Science and Technology, Kraków
 *
 * =====================================================================================
 */
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

constexpr int kOneMill =  100000;
constexpr int kTenMill = 1000000;

bool twoAdj(int number) {
    int prevDigit = 10; // different for any possible value of lastDigit
    while (number > 0) {
        int lastDigit = number % 10;
        if (lastDigit == prevDigit) {
            return true;
        }
        prevDigit = lastDigit;
        number /= 10;
    }
    return false;
}

bool notDesc(int number) {
    int prevDigit = 10; // greater than any other digit
    while (number > 0) {
        int lastDigit = number % 10;
        if (lastDigit > prevDigit) {
            return false;
        }
        prevDigit = lastDigit;
        number /= 10;
    }
    return true;
}

int main() {
    int first, last = 0;
    cin >> first
        >> last;
    cout << kOneMill << " " << kTenMill << endl;
    cout << first << " " << last << endl;
    // First criteria - digit count
    if (first < kOneMill) {
        first = kOneMill;
    }
    if (last >= kTenMill) {
        last = kTenMill - 1;
    }
    int count = 0;
    cout << "First: " << first << " and last: " << last << endl;
    for (int i = first; i <= last; i++) {
        if (twoAdj(i) and notDesc(i)) {
            count += 1;
            cout << i << endl;
        }
    }
    cout << "Result: " << count << endl;
    return 0;
}
