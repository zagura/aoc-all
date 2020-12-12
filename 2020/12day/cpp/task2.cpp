/*
 * =====================================================================================
 *
 *       Filename:  task2.cpp
 *
 *    Description:  Advent of Code 2020 - Day 12
 *
 *        Version:  0.1.0
 *        Created:  12.12.2020
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <algorithm>

struct coords {
    int x;
    int y;
};

const int revert = -1;
constexpr int dir_count = 4;

std::unordered_map<char, coords> move_change {
    { 'E', { 1, 0 }},
    { 'N', { 0, 1 }},
    { 'W', { -1, 0}},
    { 'S', { 0, -1}}
};

coords change_coords(coords pos, char direction, int value) {
    coords change = move_change.at(direction);
    pos.x += (change.x * value);
    pos.y += (change.y * value);
    return pos;
}

coords change_coords2(coords waypoint, coords ship, int value) {
    ship.x += (waypoint.x * value);
    ship.y += (waypoint.y * value);
    return ship;
}

coords rotate(coords pos, int value) {
    coords changed_pos;
    changed_pos.x = pos.x;
    changed_pos.y = pos.y;

    switch (value) {
    case 0:
        return pos;
    case 1:
        changed_pos.x = revert * pos.y;
        changed_pos.y = pos.x;
        return changed_pos;
    case 2:
        changed_pos.x = revert * pos.x;
        changed_pos.y = revert * pos.y;
        return changed_pos;
    case 3:
        changed_pos.x = pos.y;
        changed_pos.y = revert * pos.x;
        return changed_pos;
        }
        return changed_pos;
}


int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    if (!input.good()) {
        ::fprintf(stderr, "Cannot open input file\n");
        return 2;
    }
    std::vector<std::pair<char, int>> directions {};
    directions.reserve(800);
    for(std::string line; getline(input, line); ) {
        if (line.size() > 1) {
            char direction = line[0];
            int value = std::stoi(line.substr(1));
            directions.emplace_back(direction, value);
        }
    }

    coords position;
    coords waypoint_position;
    waypoint_position.x = 10;
    waypoint_position.y = 1;
    position.x = 0;
    position.y = 0;
    for (auto& [dir_change, value]: directions) {
        ::printf("Direction: %c%d\n", dir_change, value);
        switch (dir_change) {
        case 'N': case 'W': case 'E': case 'S':
            waypoint_position = change_coords(waypoint_position, dir_change, value);
            break;
        case 'L': case 'R':
            // Note: not stated in task, but changes are 90,180 or 270 degrees
            value /= 90;
            // Reverse value change if rotate in other direction
            if (dir_change == 'R') {
                value = dir_count - value;
            }
            waypoint_position = rotate(waypoint_position, value);
            break;
        case 'F':
            position = change_coords2(waypoint_position, position, value);
            break;
        }

        ::printf("Coords: (%d, %d)\n", position.x, position.y);
        ::printf("Waypoint: (%d, %d)\n", waypoint_position.x, waypoint_position.y);
    }

    if (position.x < 0) {
        position.x = revert * position.x;
    }
    if (position.y < 0) {
        position.y = revert * position.y;
    }

    int distance = position.x + position.y;
    ::printf("Task 2 result: %d\n", distance);
    return 0;
}

