/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  07.12.2019
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
#include <array>
#include <algorithm>

using std::getline;
using std::istringstream;
using std::stringstream;
using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::array;
using std::next_permutation;

// modes
// 0 - position mode
// 1 - immediate mode
constexpr size_t image_width = 25;
constexpr size_t image_height = 6;

size_t count_number(string& layer, int value) {
    int nums = 0;
    for (char c: layer) {
        if (c == '0' + value) {
            nums++;
        }
    }
    return nums;
}
size_t count_zeros(string& layer) {
    return count_number(layer, 0);
}

int checksum(string& layer) {
    int ones = count_number(layer, 1);
    int twos = count_number(layer, 2);
    return ones * twos;
}

int main() {
    string image;
    std::getline(std::cin, image);
    constexpr size_t layer_size = image_width * image_height;
    vector<string> layers;

    layers.reserve(image.size() / layer_size);
    for (size_t i = 0; i * layer_size < image.size(); i++) {
        layers.push_back(image.substr(i * layer_size, layer_size));
    }
    size_t min_zeros = layer_size;
    int checksum_value = 0;
    for (string& layer: layers) {
        size_t zeros = count_zeros(layer);
        if (zeros < min_zeros) {
            min_zeros = zeros;
            checksum_value = checksum(layer);
            cout <<"zeros: " << zeros << "   checksum " << checksum_value << endl;
        }
    }
    cout << "Checksum: " << checksum_value << endl;

    return 0;
}
