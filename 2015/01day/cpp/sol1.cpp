/*
 * =====================================================================================
 *
 *       Filename:  sol1.cpp
 *
 *    Description:  Advent of Code 2015 - Day 1, Not Quite Lisp
 *
 *        Version:  1.0
 *        Created:  29.12.2017 15:00:34
 *
 *         Author:  Michał Zagórski (zagura), <mzagorsk@student.agh.edu.pl>
 *   Organization:  AGH University of Science and Technology, Kraków
 *
 * =====================================================================================
 */

#include <iostream>

using namespace std;


int main() 
{
    string s;
    int counter = 0;
    cin >> s;

    for (auto& c: s) {
        if (c == '(')
            counter += 1;
        else if (c == ')') {
            counter -= 1;
        }
    }

    cout << counter << endl;
    return 0;
}
