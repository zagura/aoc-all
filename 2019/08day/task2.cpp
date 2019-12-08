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

int main() {
    string image;
    std::getline(std::cin, image);
    constexpr size_t layer_size = image_width * image_height;
    vector<string> layers;
    layers.reserve(image.size() / layer_size);
    for (size_t i = 0; i * layer_size < image.size(); i++) {
        layers.push_back(image.substr(i * layer_size, layer_size));
    }
    string final_layer;
    final_layer.resize(layer_size);
    for (size_t i = 0; i < layer_size; i++) {
        for (string& layer: layers) {
            if (layer[i] != '2') {
                final_layer[i] = layer[i];
                break;
            }
        }
        if (i % image_width == 0) {
            cout << endl;
        }
        switch(final_layer[i]) {
            case '0':
                cout << ' ';
                break;
            case '1':
                cout << '+';
                break;
        }
    }
    cout << endl;

    return 0;
}
