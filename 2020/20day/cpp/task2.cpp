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
     * @brief set_tile - fulfill sides table with wides of data
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

    void rotate2() {
        flipH();
        flipV();
    }

    // Unnamed change
    void change() {
        rotateL();
        flipH();
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
        //        printf("%s\n", sides[Side::up].c_str());
        //        for (size_t i = 1; i < sides[Side::left].size() - 1; i++) {
        //            printf("%c%s%c\n", sides[Side::left][i], data[i-1].c_str(), sides[Side::right][i]);
        //        }
        //        printf("%s\n", sides[Side::down].c_str());
        //        printf("=========\n");
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
/// Unordered couple between two tiles which match with sides
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

// Return opposite side
Side opposite(Side side) {
    switch (side) {
    case Side::down:
        return Side::up;
    case Side::right:
        return Side::left;
    case Side::up:
        return Side::down;
    case Side::left:
        return Side::right;
        break;
    }
    return Side::right;
}

string str_side(Side side) {
    switch (side) {
    case Side::down:
        return "down";
    case Side::right:
        return "right";
    case Side::up:
        return "up";
    case Side::left:
        return "left";
    }
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

int try_match(vector<string>& tiles) {
    static const vector<string> pattern = {
        "                  # ",
        "#    ##    ##    ###",
        " #  #  #  #  #  #   "
    };
    int count = 0;
    static const size_t width = pattern.front().size();
    static const size_t height = pattern.size();
    for (size_t row = 0; row < tiles.size() - height; row++) {
        for (size_t column = 0; column < tiles.front().size() - width; column++) {
            if (is_sea_monster(tiles, pattern, row, column)) {
                mark_monster(tiles, pattern, row, column);
            }
        }
    }
    for (const auto& row: tiles) {
        for (const auto& c: row) {
            if (c == '#') {
                count++;
            }
        }
    }
    return count;
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
            //            printf("line: %s\n", line.c_str());
            //            printf("line.substr: %s\n", line.substr(5, 4).c_str());
            int id = std::stoi(line.substr(5, 4));
            current_tile.id = id;
        } else {
            current_tile.data.push_back(line);
        }
    }

    printf("Total tiles %zu\n", input_tiles.size());
    for (auto& t: input_tiles) {
        t->set_tile();
        printf("Tile id: %d\n", t->id);
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
    //    Tile t = *input_tiles.front();
    //    t.print();
    //    for (int i = 0; i < kSidesCount; i++) {
    //        t.rotateR();
    //        t.print();
    //    }

    //    return 0;
    /// First setup image[0][0] as tile with matches on right and down
    int id = unmatched.front();
    vector<TMatch> matches = find_matches(tiles[id], input_tiles);
    while (matches[0].sides.first != Side::right) {
        //        printf("Matches[0] side: %d\n", matches[0].sides.first);
        //        printf("Matches[1] side: %d\n", matches[1].sides.first);
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
            printf("Before: (%zu, %zu)\n", row, column);
            matches = find_matches(image[row][column - 1], input_tiles);
            for (auto& tm: matches) {
                printf("Match (%d, %d), (%s, %s), %s\n", tm.ids.first, tm.ids.second,
                       str_side(tm.sides.first).c_str(),
                       str_side(tm.sides.second).c_str(),
                       (tm.reverse ? "True" : "False"));
                if (tm.sides.first == Side::right) {
                    tptr other_tile = tiles[tm.ids.second];
                    printf("Find match with tile: %d \t", other_tile->id);
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
                    image[row][column - 1]->set_tile();
                    other_tile->set_tile();
                    check_sides(image[row][column -1], other_tile, matches);
                    if (matches.back().reverse) {
                        other_tile->flipH();
                    }
                    printf("(%zu, %zu) %d -> %d\n", row, column, tm.reverse, matches.back().reverse);
                    image[row][column] = other_tile;
                    break;
                }
            }
        }
        if (row != kMapSize - 1) {
            matches = find_matches(image[row][0], input_tiles);
            for (auto& tm: matches) {
                if (tm.sides.first == Side::down) {
                    printf("Match down (%d, %d), (%s, %s), %s\n", tm.ids.first, tm.ids.second,
                           str_side(tm.sides.first).c_str(),
                           str_side(tm.sides.second).c_str(),
                           (tm.reverse ? "True" : "False"));
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
                    image[row][0]->set_tile();
                    other_tile->set_tile();
                    check_sides(image[row][0], other_tile, matches);
                    if (matches.back().reverse) {
                        other_tile->flipV();
                    }
                    printf("(%zu, %zu)\n", row + 1, static_cast<size_t>(0));
                    image[row + 1][0] = other_tile;
                    break;
                }
            }
        }
    }


    /// Print whole image with borders
    printf("Total map\n\n");
    for (size_t row = 0; row < kMapSize; row++) {
        for (size_t subrow = 0; subrow < image[row].front()->data.size(); subrow++) {
            for (size_t column = 0; column < kMapSize; column++) {
                printf("%s ", image[row][column]->data[subrow].c_str());
            }
            printf("\n");
        }
        printf("\n");
    }

    for (size_t row = 0; row < kMapSize; row++) {
        for (size_t column = 0; column < kMapSize; column++) {
            if (image[row][column]) {
                printf("%d ", image[row][column]->id);
                //                image[row][column]->print();
            }
        }
        printf("\n");
    }
    printf("\n");

    for (size_t row = 0; row < kMapSize; row++) {
        for (size_t column = 0; column < kMapSize; column++) {
            image[row][column]->remove_borders();
        }
    }

    printf("Total map\n\n");
    vector<string> data {};
    for (size_t row = 0; row < kMapSize; row++) {
        for (size_t subrow = 0; subrow < image[row].front()->data.size(); subrow++) {
            string merged_row = {};
            for (size_t column = 0; column < kMapSize; column++) {
                printf("%s ", image[row][column]->data[subrow].c_str());
                merged_row += image[row][column]->data[subrow];
            }
            data.push_back(merged_row);
            printf("\n");
        }
        printf("\n");
    }
    printf("\n");

    Tile main_tile {};
    main_tile.data = data;
    main_tile.rotateR();
    main_tile.flipV();
    result = try_match(main_tile.data);
    for (auto& s: main_tile.data) {
        printf("%s\n", s.c_str());
    }
    printf("Answer: %llu\n", result);
    return 0;
}

