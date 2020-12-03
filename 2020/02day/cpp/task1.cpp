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
#include <string>
#include <vector>
#include <cinttypes>
#include <fmt/format.h>
#include <map>

using std::string;

int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }

    int valid_password_count = 0;
    for (std::string line; getline(input, line);) {
        if (line == "\n") {
            // Skip empty line
            continue;
        }
        std::stringstream stream { line };
        // separators: '-', ' ', ' '
        string token;
        getline(stream, token, '-');
        int minimal = std::stoi(token);
        getline(stream, token, ' ');
        int maximal = std::stoi(token);
        getline(stream, token, ' ');
        char letter = token[0];
        getline(stream, token);
        string pwd = token;
        /// Verify record
        //::printf("Record: %d to %d of letter %c in pwd: %s\n",
        //         minimal, maximal, letter, pwd.c_str());
        int count = std::count_if(pwd.begin(), pwd.end(),
                                  [&](char c) {return c == letter;});
        if (minimal <= count && count <= maximal) {
            valid_password_count++;
        }
    }
    ::printf("Task 1 result: %d", valid_password_count);
    return 0;
}
