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

using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::getline;
using std::stringstream;

int main() {
    string floors;
    getline(std::cin, floors);
    int floor = 0;
    for (char c: floors) {
        switch (c) {
            case '(':
                floor++;
                break;
            case ')':
                floor--;
                break;
        }
    }
    cout << "Task 1 answer: " << floor << endl;
    return 0;
}

