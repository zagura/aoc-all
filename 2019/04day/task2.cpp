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
#include <array>

using std::array;
using std::cin;
using std::cout;
using std::endl;

constexpr int kOneMill =  100000;
constexpr int kTenMill = 1000000;
constexpr int kArrSize = 1 + 6 + 2;
bool twoAdj(int number) {
    int tab[] = { 12, 0, 0, 0, 0, 0, 0, 11, 10 };
    int index = 1;
    while (number > 0) {
        int lastDigit = number % 10;
        tab[index] = lastDigit;
        number /= 10;
        index++;
    }
    for (int i = 1; i < 7; i++) {
        int val = tab[i];
        if (val == tab[i+1]) {
            if ((tab[i+2] != val) && (tab[i-1] != val)) {
                return true;
            }
        }
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
