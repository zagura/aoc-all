/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Day 14 - Space Stoichometry
 *
 *        Version:  1.0
 *        Created:  17.12.2019
 *
 *         Author:  Michał Zagórski (zagura), <mzagorsk@student.agh.edu.pl>
 *   Organization:  AGH University of Science and Technology, Kraków
 *
 * =====================================================================================
 */
#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include <string>
#include <array>
#include <algorithm>
#include <queue>

using namespace std;


struct Node {
    int id;
    int target_amount;
    vector<pair<int, int>> neighbors;
};

void program(vector<Node>& nodes) {
    map<int, int> amounts { { 1, 1 }};
    queue<int> q;
    q.push(1);
    while (not q.empty()) {
        int node_id = q.front();
        q.pop();
        Node& node = nodes[node_id];
        if (node_id == 0) {
            continue;
        }
        int base_amount = node.target_amount;
        int required_amount = amounts[node_id];
        if (required_amount < 0) {
            required_amount = 0;
        }
        int mul = required_amount / base_amount
                + ((required_amount % base_amount > 0) ? 1 : 0);
        for (auto& p: node.neighbors) {
            q.push(p.first);
            amounts[p.first] += mul * p.second;
        }
        if (node_id != 0) {
            amounts[node_id] -= mul * base_amount;
        }
    }
    cout << amounts[0] << endl;
//    int current_node = 1;
}

int main() {
    map <string, int> names;
    names["ORE"] = 0;
    names["FUEL"] = 1;
    string line;
    vector<Node> nodes;
    nodes.resize(100);
    while (getline(std::cin, line)) {
        stringstream ss { line };
        string ingridients;
        vector<pair<int, int>> receipt;
        getline(ss, ingridients, '=');
//        cout << "Ingridients: " << ingridients << endl;
        {
            stringstream left_side { ingridients };
            for(string single; getline(left_side, single, ',');) {
                stringstream single_part { single };
                int amount;
                string name;
                single_part >> amount >> name;
//                cout << "Ingridient: " << amount << "  " << name << endl;
                int id;
                if (names.find(name) != names.end()) {
                    id = names.at(name);
                } else {
                    id = names.size();
                    names[name] = id;
                }
                receipt.emplace_back(id, amount);
            }
        }
        string result;
        getline(ss, result, '=');
//        cout << "Right side: " << result.substr(1) << endl;
        stringstream result_ss { result.substr(1) };
        int amount;
        string name;
        int id;
        result_ss >> amount >> name;
        if (names.find(name) != names.end()) {
            id = names.at(name);
        } else {
            id = names.size();
            names[name] = id;
        }
        Node node;
        node.id = id;
        node.neighbors = receipt;
        node.target_amount = amount;
        nodes[id] = node;
    }
    nodes.resize(names.size());
    /// Here we have full graph, let's find path from 1 to 0 and get count.
    program(nodes);
    return 0;
}
