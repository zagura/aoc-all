/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02.12.2019 21:22:50
 *
 *         Author:  Michał Zagórski (zagura), <mzagorsk@student.agh.edu.pl>
 *   Organization:  AGH University of Science and Technology, Kraków
 *
 * =====================================================================================
 */
#include <iostream>
#include <sstream>
#include <vector>
#include <string>


using std::getline;
using std::istringstream;
using std::string;
using std::vector;
using std::cout;
using std::endl;

int main() {
    std::vector<int> vals;
    vals.reserve(100);
    for (std::string number; getline(std::cin, number, ',');) {
        vals.push_back(std::stoi(number));
    }
    for (size_t i = 0; i < vals.size(); i += 4) {
        int v1 = 0;
        int v2 = 0;
        int v3 = 0;
        switch(vals[i]) {
            case 1:
                v1 = vals.at(vals[i+1]);
                v2 = vals.at(vals[i+2]);
                v3 = v1 + v2;
                vals[vals[i+3]] = v3;
        		break;
            case 2:
                v1 = vals.at(vals[i+1]);
                v2 = vals.at(vals[i+2]);
                v3 = v1 * v2;
                vals[vals[i+3]] = v3;
	        	break;
            case 99:
                std::cout << "End of program" << std::endl;
                i = vals.size() + 1;
                break;
        }
    }

    for (auto& v: vals) {
        cout << v << ",";
    }
    cout << endl;


    return 0;
}
