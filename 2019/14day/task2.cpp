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
using amount_type = int64_t;
constexpr amount_type kTrillion = 1000000000000;
struct Node {
    int id;
    amount_type target_amount;
    vector<pair<int, amount_type>> neighbors;
};
string over_trillion(amount_type amount) {
    if (amount >= kTrillion) {
        return "true";
    }
    return "false";
}

bool program(vector<Node>& nodes, amount_type total_amount) {
    map<int, amount_type> amounts { { 1, total_amount}};
    queue<int> q;
    q.push(1);
    while (not q.empty()) {
        int node_id = q.front();
        q.pop();
//        if (amounts[node_id] < 0) {
//            cout << "node: " << node_id << " | amount: " << amounts[node_id] << endl;
//        }
        Node& node = nodes[node_id];
        if (node_id == 0) {
            continue;
        }
        amount_type base_amount = node.target_amount;
        amount_type required_amount = amounts[node_id];
        amount_type mul = required_amount / base_amount
                + ((required_amount % base_amount > 0) ? 1 : 0);
        for (auto& p: node.neighbors) {
            q.push(p.first);
            amounts[p.first] += mul * p.second;
        }
        if (node_id != 0) {
            amounts[node_id] -= mul * base_amount;
        }
    }
    cout << total_amount << ": " << amounts[0] << " | " << over_trillion(amounts[0]) << endl;
    return (amounts[0] > kTrillion);
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
        vector<pair<int, amount_type>> receipt;
        getline(ss, ingridients, '=');
//        cout << "Ingridients: " << ingridients << endl;
        {
            stringstream left_side { ingridients };
            for(string single; getline(left_side, single, ',');) {
                stringstream single_part { single };
                amount_type amount;
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
        amount_type amount;
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
    /// Part 2 made semi-manual. Find the amount of fuel, when needed ORE overflow 10^12.
    amount_type init_amount = 6226100;
    for (amount_type a = init_amount; init_amount < init_amount + 100 ; a+= 1) {
        if (program(nodes, a)) {
            break;
        }
    }
    return 0;
}
