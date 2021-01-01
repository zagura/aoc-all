/*
 * =====================================================================================
 *
 *       Filename:  task2.cpp
 *
 *    Description:  Advent of Code 2020 - Day 22
 *
 *        Version:  0.1.0
 *        Created:  22.12.2020
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
#include <queue>
#include <utility>
#include <vector>
#include <cinttypes>

using std::string;
using std::vector;
using std::array;
using std::map;
using std::stringstream;
using std::queue;
using std::pair;
using deck = std::pair<queue<int>, queue<int>>;
uint64_t get_result(std::queue<int> q) {
    uint64_t result = 0;
    for(uint64_t mul = q.size(); !q.empty(); --mul) {
        result += (mul * static_cast<uint64_t>(q.front()));
        q.pop();
    }
    return result;
}

enum Player {
    first = 0,
    second = 1
};

void print_cards(int id, std::queue<int> p) {
    uint64_t res = get_result(p);
    printf("Player %d's deck: ", id);
    while(!p.empty()) {
        printf("%d, ", p.front());
        p.pop();
    }
//    printf("\t\t%" PRIu64 "\n", res);
    printf("\n");
}
void print_deck(const deck& round, int round_no, int game) {
    printf("-- Round %d (Game %d) --\n", round_no, game);
    print_cards(1, round.first);
    print_cards(2, round.second);
}

queue<int> reduce (queue<int> q0, int size) {
    queue<int> q;
    while(size--) {
        q.push(q0.front());
        q0.pop();
    }
    return q;
}

static int game_no = 1;
std::pair<Player, uint64_t> play_game_recurse(std::queue<int> p1, std::queue<int> p2) {
//    printf("=== Game %d ===\n\n", game_no);
    int the_game = game_no;
    uint64_t round_no = 1;
    vector<pair<queue<int>, queue<int>>> history {};
//    history.resize(1);
    history.reserve(p1.size() * p2.size());
    while ((not p1.empty()) and (not p2.empty())) {
        auto round = std::make_pair(p1, p2);
        if (std::find(history.begin(), history.end(), round) != history.end()) {
//            print_deck(round, round_no, the_game);
            return std::make_pair(Player::first, get_result(p1));
        } else {
            history.push_back(round);
        }
//        print_deck(round, round_no, the_game);
        int card1 = p1.front();
        p1.pop();
        int card2 = p2.front();
        p2.pop();
//        printf("Player 1 plays: %d\nPlayer 2 plays: %d\n", card1, card2);
        Player winner = (card2 > card1) ? Player::second : Player::first;
        std::pair<Player, uint64_t> last_result;
        if ((card1 <= p1.size()) and (card2 <= p2.size())) {
            game_no++;
//            int new_game = game_no;
//            printf("Playing a sub-game to determine the winner...\n\n");
            last_result = play_game_recurse(reduce(p1, card1), reduce(p2, card2));
//            printf("The winner of game %d is player %d!\n", new_game, last_result.first == Player::first ? 1 : 2);
//            printf("\n...anyway, back to game %d.\n", the_game);
            winner = last_result.first;
        }
//        printf("Player %d wins round %" PRIu64 " of game %d!\n\n", winner == Player::first ? 1 : 2, round_no, the_game);
        if (winner == Player::second) {
            p2.push(card2);
            p2.push(card1);
        } else if (winner == Player::first) {
            p1.push(card1);
            p1.push(card2);
        }
        round_no++;
    }
    if (p1.empty()) {
        return std::make_pair(Player::second, get_result(p2));
    }
    return std::make_pair(Player::first, get_result(p1));
}

std::pair<Player, uint64_t> play_game(std::queue<int> p1, std::queue<int> p2) {
    uint64_t round_no = 0;
    while ((not p1.empty()) and (not p2.empty())) {
        int card1 = p1.front();
        p1.pop();
        int card2 = p2.front();
        p2.pop();
        Player winner = (card2 > card1) ? Player::second : Player::first;
        if (winner == Player::second) {
            p2.push(card2);
            p2.push(card1);
        } else if (winner == Player::first) {
            p1.push(card1);
            p1.push(card2);
        }
        round_no++;
    }
    if (p1.empty()) {
        return std::make_pair(Player::second, get_result(p2));
    }
    return std::make_pair(Player::first, get_result(p1));
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
    uint64_t result = 0;
    queue<int> p1 {};
    queue<int> p2 {};
    bool first_deck = true;
    for (string line; getline(input, line); ) {
        if (line.empty()) {
            first_deck = not first_deck;
            continue;
        } else if (line.front() == 'P') {
            // Player header
            continue;
        }
        if (first_deck) {
            p1.push(std::stoi(line));
        } else {
            p2.push(std::stoi(line));
        }
    }
    result = play_game_recurse(p1, p2).second;
    ::printf("Task 1 result: %" PRIu64 "\n", play_game(p1, p2).second);
    ::printf("Task 2 result: %" PRIu64 "\n", result);
    return 0;
}

