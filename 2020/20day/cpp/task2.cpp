/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2020 - Day 20
 *
 *        Version:  0.2.0
 *        Created:  06.01.2021
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <array>
#include <map>
#include <vector>
#include <memory>

using std::string;
using std::vector;
using std::array;
using std::map;
using std::stringstream;
//constexpr size_t kMapSize = 12; // Total of 144 tiles

enum Side: int {
    up = 0,
    right = 1,
    down = 2,
    left = 3
};
constexpr int kSidesCount = 4;

struct Tile {
    int id = 0;
    vector<string> data {};
    array<string, 4> sides {};
    /**
     * @brief set_tile - fill sides table with wides of data
     */
    void set_tile() {
        /// Both sides order: **left to right**
        /// and **up to down**
        // up, left, right, down
        sides[Side::up] = data.front();
        sides[Side::down] = data.back();
        string left {};
        string right {};
        for (auto s: data) {
            left += s.front();
            right += s.back();
        }
        sides[Side::left] = left;
        sides[Side::right] = right;
    }
    void flipV() {
        for(auto& s: data) {
            std::reverse(s.begin(), s.end());
        }
        set_tile();
    }
    void flipH() {
        std::reverse(data.begin(), data.end());
        set_tile();
    }
    void rotateR() {
        vector<string> data_copy = data;
        for (size_t row = 0; row < data.size(); row++) {
            string new_row = "";
            for (size_t column = 0; column < data.front().size(); column++) {
                new_row += data[data.front().size() - 1 - column][row];
            }
            data_copy[row] = new_row;
        }
        data = data_copy;
        set_tile();
    }

    void rotateL() {
        vector<string> data_copy {};
        data_copy.resize(data.size());

        for (size_t row = 0; row < data.size(); row++) {
            string new_row = "";
            for (size_t column = 0; column < data.front().size(); column++) {
                new_row += data[column][data.size() - 1 - row];
            }
            data_copy[row] = new_row;
        }
        set_tile();
        data = data_copy;
    }

    void print() {
        printf("Id: %d\n", id);
        printf("%s, %s, %s, %s\n",
               sides[0].c_str(), sides[1].c_str(),
               sides[2].c_str(), sides[3].c_str());
        printf("Data: \n");
        for (auto& s: data) {
            printf("%s\n", s.c_str());
        }
        printf("________\n");
        printf("Corners match: %d, %d, %d, %d\n",
               sides[Side::up].front() == sides[Side::left].front(),
               sides[Side::up].back() == sides[Side::right].front(),
               sides[Side::down].front() == sides[Side::left].back(),
               sides[Side::down].back() == sides[Side::right].back());
    }

    void remove_borders() {
        // update sides before removing them from data
        set_tile();
        data.erase(data.begin());
        data.pop_back();
        for (auto& s: data) {
            s = s.substr(1, s.size() - 2);
        }
    }
};
using tptr = std::shared_ptr<Tile>;

vector<int> get_unmatched_tiles (const vector<tptr>& tiles) {
    vector<int> unmatched {};
    /// Part 1
    for (auto& first_tile: tiles) {
        int match = 0;
        for (auto& other_tile: tiles) {
            if (other_tile->id != first_tile->id) {
                for (size_t side = 0; side < kSidesCount; side++) {
                    for(size_t side2 = 0; side2 < kSidesCount; side2++) {
                        std::string reversed = other_tile->sides[side2];
                        std::reverse(reversed.begin(), reversed.end());
                        if (other_tile->sides[side2] == first_tile->sides[side]
                            || reversed == first_tile->sides[side]) {
                            match++;
                            break;
                        }
                    }
                }
            }
        }
        // Corners match only with two sides
        // borders with 3
        // rest with 4
        if (match == 2) {
            printf("Not matched for id: %d\n", first_tile->id);
            unmatched.push_back(first_tile->id);
        }
    }
    return unmatched;
}
/// two tiles which match sides
struct TMatch {
    std::pair<int, int> ids;
    std::pair<Side, Side> sides;
    bool reverse;
    TMatch() = default;
    TMatch(const tptr& t1, const tptr& t2, Side side1, Side side2, bool r)
        : ids(t1->id, t2->id),
        sides(side1, side2),
        reverse(r) {}
};
void check_sides(const tptr& tile, const tptr& other, vector<TMatch>& matched) {
    for (size_t side = 0; side < kSidesCount; side++) {
        for(size_t side2 = 0; side2 < kSidesCount; side2++) {
            std::string reversed = other->sides[side2];
            std::reverse(reversed.begin(), reversed.end());
            if (other->sides[side2] == tile->sides[side]
                || reversed == tile->sides[side]) {
                TMatch tm (tile, other, static_cast<Side>(side),
                          static_cast<Side>(side2), (reversed == tile->sides[side]));
                matched.push_back(tm);
                return;
            }
        }
    }
}

vector<TMatch> find_matches(const tptr& tile, const std::vector<tptr>& all_tiles) {
    vector<TMatch> matched{};
    for(const auto& other: all_tiles) {
        if (other->id != tile->id) {
            check_sides(tile, other, matched);
        }
    }
    return matched;
}

map<int, vector<TMatch>> find_matches(const std::vector<tptr>& tiles,
                                      const std::vector<tptr>& all_tiles) {
    map<int, vector<TMatch>> match {};
    for(const auto& tile: tiles) {
        match[tile->id] = find_matches(tile, all_tiles);
    }
    return match;
}

vector<std::pair<int, int>> get_coords(const vector<string>& pattern) {
    vector<std::pair<int, int>> result {};
    result.reserve(20);
    for (size_t row = 0; row < pattern.size(); row++) {
        for (size_t column = 0; column < pattern.front().size(); column++) {
            if (pattern[row][column] == '#') {
                result.emplace_back(row, column);
            }
        }
    }
    return result;
}

bool is_sea_monster(const vector<string>& tiles, const vector<string>& pattern,
                    size_t row, size_t column) {
    for (auto [r, c]: get_coords(pattern)) {
        if (tiles[row + r][column + c] != '#') {
            return false;
        }
    }
    return true;
}

void mark_monster(vector<string>& tiles, const vector<string>& pattern,
                    size_t row, size_t column) {
    for (auto [r, c]: get_coords(pattern)) {
        tiles[row + r][column + c] = 'O';
    }
}

int count_fields(const vector<string>& tiles) {
    int count = 0;
    for (const auto& row: tiles) {
        for (const auto& c: row) {
            if (c == '#') {
                count++;
            }
        }
    }
    return count;
}

int try_match(vector<string>& tiles) {
    static const vector<string> pattern = {
        "                  # ",
        "#    ##    ##    ###",
        " #  #  #  #  #  #   "
    };
    static const size_t width = pattern.front().size();
    static const size_t height = pattern.size();
    for (size_t row = 0; row < tiles.size() - height; row++) {
        for (size_t column = 0; column < tiles.front().size() - width; column++) {
            if (is_sea_monster(tiles, pattern, row, column)) {
                mark_monster(tiles, pattern, row, column);
            }
        }
    }
    return count_fields(tiles);
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
    long long int result = 0;
    vector<tptr> input_tiles;
    Tile current_tile = {};
    for (string line; getline(input, line); ) {
        if (line.empty()) {
            input_tiles.push_back(std::make_shared<Tile>(current_tile));
            current_tile = Tile {};
        } else if (line.back() == ':') {
            int id = std::stoi(line.substr(5, 4));
            current_tile.id = id;
        } else {
            current_tile.data.push_back(line);
        }
    }

    for (auto& t: input_tiles) {
        t->set_tile();
    }
    size_t kMapSize = 3;
    while (kMapSize * kMapSize < input_tiles.size()) {
        kMapSize++;
    }
    vector<int> unmatched = get_unmatched_tiles(input_tiles);
    result = 1;
    for (auto& id: unmatched) {
        result *= static_cast<long long int>(id);
    }
    ::printf("Task 1 result: %lld\n", result);


    /// Part 2
    // 12 x 12 grid of tiles
    // kMapSize x kMapSize (3x3 in example)
    std::vector<std::vector<tptr>> image;
    image.resize(kMapSize);
    for(auto& row: image) {
        row.resize(kMapSize);
    }
    /// Generate map tile_id -> tile object
    std::unordered_map<int, tptr> tiles;
    for (auto& t: input_tiles) {
        tiles.emplace(t->id, t);
    }


    /// First setup image[0][0] as tile with matches on right and down
    int id = unmatched.front();
    vector<TMatch> matches = find_matches(tiles[id], input_tiles);
    while (matches[0].sides.first != Side::right) {
        tiles[id]->rotateL();
        matches = find_matches(tiles[id], input_tiles);
    }
    if (matches[0].reverse) {
        tiles[id]->flipH();
    }
    matches = find_matches(tiles[id], input_tiles);
    if (matches[1].sides.first == Side::up) {
        tiles[id]->flipH();
    }

    image[0][0] = tiles[id];
    for (size_t row = 0; row < kMapSize; row++) {
        for (size_t column = 1; column < kMapSize; column++) {
            matches = find_matches(image[row][column - 1], input_tiles);
            for (auto& tm: matches) {
                if (tm.sides.first == Side::right) {
                    tptr other_tile = tiles[tm.ids.second];
                    switch (tm.sides.second) {
                    case Side::down:
                        other_tile->rotateL();
                        [[fallthrough]];
                    case Side::right:
                        other_tile->rotateL();
                        [[fallthrough]];
                    case Side::up:
                        other_tile->rotateL();
                        [[fallthrough]];
                    case Side::left:
                        break;
                    }
                    other_tile->set_tile();
                    check_sides(image[row][column -1], other_tile, matches);
                    if (matches.back().reverse) {
                        other_tile->flipH();
                    }
                    image[row][column] = other_tile;
                    break;
                }
            }
        }
        if (row != kMapSize - 1) {
            matches = find_matches(image[row][0], input_tiles);
            for (auto& tm: matches) {
                if (tm.sides.first == Side::down) {
                    tptr other_tile = tiles[tm.ids.second];
                    switch (tm.sides.second) {
                    case Side::left:
                        other_tile->rotateL();
                        [[fallthrough]];
                    case Side::down:
                        other_tile->rotateL();
                        [[fallthrough]];
                    case Side::right:
                        other_tile->rotateL();
                        [[fallthrough]];
                    case Side::up:
                        break;
                    }
                    other_tile->set_tile();
                    check_sides(image[row][0], other_tile, matches);
                    if (matches.back().reverse) {
                        other_tile->flipV();
                    }
                    image[row + 1][0] = other_tile;
                    break;
                }
            }
        }
    }

    for (size_t row = 0; row < kMapSize; row++) {
        for (size_t column = 0; column < kMapSize; column++) {
            image[row][column]->remove_borders();
        }
    }

    vector<string> data {};
    for (size_t row = 0; row < kMapSize; row++) {
        for (size_t subrow = 0; subrow < image[row].front()->data.size(); subrow++) {
            string merged_row = {};
            for (size_t column = 0; column < kMapSize; column++) {
                merged_row += image[row][column]->data[subrow];
            }
            data.push_back(merged_row);
        }
    }

    int minimum = count_fields(data);
    vector<string> final_map = data;
    Tile main_tile {};
    main_tile.data = data;
    result = try_match(main_tile.data);
    if (result < minimum) {
        minimum = result;
        final_map = main_tile.data;
    }

    main_tile.data = data;
    main_tile.flipH();
    result = try_match(main_tile.data);
    if (result < minimum) {
        minimum = result;
        final_map = main_tile.data;
    }

    main_tile.data = data;
    main_tile.rotateR();
    result = try_match(main_tile.data);
    if (result < minimum) {
        minimum = result;
        final_map = main_tile.data;
    }

    main_tile.data = data;
    main_tile.rotateR();
    main_tile.flipH();
    result = try_match(main_tile.data);
    if (result < minimum) {
        minimum = result;
        final_map = main_tile.data;
    }
    main_tile.data = data;
    main_tile.rotateR();
    main_tile.rotateR();
    result = try_match(main_tile.data);
    if (result < minimum) {
        minimum = result;
        final_map = main_tile.data;
    }

    main_tile.data = data;
    main_tile.rotateR();
    main_tile.rotateR();
    main_tile.flipH();
    result = try_match(main_tile.data);
    if (result < minimum) {
        minimum = result;
        final_map = main_tile.data;
    }
    main_tile.data = data;
    main_tile.rotateR();
    main_tile.rotateR();
    main_tile.rotateR();
    result = try_match(main_tile.data);
    if (result < minimum) {
        minimum = result;
        final_map = main_tile.data;
    }
    main_tile.data = data;
    main_tile.rotateR();
    main_tile.rotateR();
    main_tile.rotateR();
    main_tile.flipH();
    result = try_match(main_tile.data);
    if (result < minimum) {
        minimum = result;
        final_map = main_tile.data;
    }

    for (auto& s: final_map) {
        ::printf("%s\n", s.c_str());
    }
    ::printf("Part 2 result: %d\n", minimum);
    return 0;
}

