/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  05.12.2019 18:52:38
 *
 *         Author:  Michał Zagórski (zagura), <mzagorsk@student.agh.edu.pl>
 *   Organization:  AGH University of Science and Technology, Kraków
 *
 * =====================================================================================
 */

#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include <vector>
#include <list>
#include <queue>

using std::cin;
using std::cout;
using std::getline;
using std::stringstream;
using std::string;
using std::map;
using std::make_pair;
using std::vector;
using std::pair;
using std::list;
using std::queue;

vector<int> bfs(vector<vector<int>> g) {
    vector<int> distances {};
    vector<bool> visited(g.size(), false);
    distances.resize(g.size());
    /// Pair <node_id, distance>
    queue<pair<int, int>> q;
    q.emplace(0, 0);
    while (!q.empty()) {
        auto node = q.front();
        q.pop();
        int current_node = node.first;
        if (!visited[current_node]) {
            visited[current_node] = true;
            distances[current_node] = node.second;
            for (int neighbour: g[current_node]) {
                q.emplace(neighbour, node.second + 1);
            }
        }
    }
    return distances;
}

pair< map<string,int>, vector<vector<int>> > read_input() {
    map<string, int> ids{};
    vector<vector<int>> graph {};
    int count = 1;
    ids.insert(make_pair("COM", 0));
    graph.resize(1);
    for (string line; getline(std::cin, line);) {
        stringstream ss { line };
        string vertex1, vertex2;
        getline(ss, vertex1, ')');
        getline(ss, vertex2, ')');
        int id1 = 0 , id2 = 0;
        if (ids.find(vertex1) != ids.end()) {
               id1 = ids.at(vertex1);
        } else {
            id1 = count;
            ids.emplace(vertex1, id1);
            vector <int> vec;
            graph.push_back(vec);
            count++;
        }
        if (ids.find(vertex2) != ids.end()) {
            id2 = ids.at(vertex2);
        } else {
            id2 = count;
            ids.emplace(vertex2, id2);
            vector<int> vec {};
            graph.push_back(vec);
            count++;
        }
        graph[id1].push_back(id2);
        graph[id2].push_back(id1);
    }
    return make_pair(ids, graph);
}

int main() {

    map<string, int> ids;
    vector<vector<int>> graph;
    auto result = read_input();
    cout << "Graph size: " << result.second.size() << std::endl;
    ids = result.first;
    graph = result.second;
    vector<int> distances = bfs(graph);
    int total_sum = 0;
    for (int d: distances) {
        total_sum += d;
    }
    cout << "Total distance: " << total_sum << std::endl;
    return 0;
}
