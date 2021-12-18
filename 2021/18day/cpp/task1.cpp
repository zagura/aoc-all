/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2021 - Day 18 "Snailfish"
 *
 *        Version:  0.1.0
 *        Created:  18.12.2021
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
#include <cinttypes>
#include <cctype>
#include <variant>

using std::string;
using std::vector;
using std::array;
using std::map;
using std::stringstream;

struct number {
    number* left = nullptr;
    number* right = nullptr;
    number* parent = nullptr;
    int value = 0;
};

struct parse_number {
    int state;
    number* left = nullptr;
    number* right = nullptr;
};

number* parsing_number(const std::string& s) {
    std::vector<parse_number> not_parsed {};
    number* n;
    for (auto c: s) {
        if (c == '[') {
            not_parsed.emplace_back();
        } else if (std::isdigit(static_cast<unsigned char>(c))) {
            auto& pn = not_parsed.back();
            if (pn.state == 0) {
                pn.left = new number();
                pn.left->value = c - '0';
                pn.state = 1;
            } else if (pn.state == 2) {
                pn.right = new number();
                pn.right->value = c - '0';
                pn.state++;
            }
        } else if (c == ',') {
             not_parsed.back().state++;
        } else if (c == ']') {
            number* current_number = new number();
            current_number->left = not_parsed.back().left;
            current_number->left->parent = current_number;
            current_number->right = not_parsed.back().right;
            current_number->right->parent = current_number;
            not_parsed.pop_back();
            if (not_parsed.empty()) {
                n = current_number;
            } else {
                auto& parent = not_parsed.back();
                if (parent.state == 0) {
                    parent.left = current_number;
                    parent.state++;
                } else if (parent.state == 2) {
                    parent.right = current_number;
                    parent.state++;
                }
            }
        }
    }
    return n;
}

void print(const number& n) {
    if (n.left  == nullptr && n.right == nullptr) {
        printf("%d", n.value);
        return;
    }
    printf("[");
    if (n.left != nullptr) {
        print(*n.left);
    } else {
        printf("%d", n.value);
    }
    printf(",");
    if (n.right != nullptr) {
        print(*n.right);
    } else {
        printf("%d", n.value);
    }
    printf("]");
}

void clear(number& n) {
    if (n.left != nullptr) {
        clear(*n.left);
        delete n.left;
        n.left = nullptr;
    }
    if (n.right != nullptr) {
        clear(*n.right);
        delete n.right;
        n.right = nullptr;
    }
}

std::pair<number*, int> first(number* current, int level) {
    while (current->left) {
        current = current->left;
        level++;
    }
    return std::make_pair(current, level);
}

std::pair<number*, int> last(number* current, int level) {
    while (current->right) {
        current = current->right;
        level++;
    }
    return std::make_pair(current, level);
}

std::pair<number*, int> next(number* current, int level) {
//    printf("Next: %p: %d", current, level);
    while (current->parent) {
//        printf("Next-inwhile: %p: %d\n", current, level);
        if (current->parent->left == current) {
            if (current->parent->right) {
                current = current->parent->right;
                return first(current, level);
            }
            break;
        } else {
            current = current->parent;
            level--;
        }
    }
    return std::make_pair(nullptr, 0);
}

std::pair<number*, int> prev(number* current, int level) {
    while (current->parent) {
        if (current->parent->right == current) {
            if (current->parent->left) {
                current = current->parent->left;
                return last(current, level);
            }
            break;
        } else {
            current = current->parent;
            level--;
        }
    }
    return std::make_pair(nullptr, 0);
}

bool split(number* n, int level) {
    if (n->value >= 10) {
        printf("In split - level %d :", level);
        print(*n);
        printf("\n");
        int value = n->value;
        n->left = new number;
        n->left->parent = n;
        n->right = new number;
        n->right->parent = n;
        n->left->value = value / 2;
        n->right->value = (value / 2) + (value % 2);
        n->value = 0;
        return true;
    }
    return false;
}

bool explode(number* current, int level) {
    // We jump over leafs, which would have level 5 in the case
    if (level == 5) {
        auto n = current->parent;
        printf("In explode - level %d :", level - 1);
        print(*n);
        printf("\n");
        if (n->left && n->right) {
            int left_val = n->left->value;
            int right_val = n->right->value;
            clear(*n);
            n->value = 0;
            number* left_node = prev(n, level).first;
            if (left_node) { left_node->value += left_val; }
            number* right_node = next(n, level).first;
            if (right_node) { right_node->value += right_val; }
            return true;
        }
    }
    return false;
}

bool reduce(number* head) {
    std::pair<number*, int> data = first(head, 0);
    while (data.first != nullptr) {
//        printf("Value %p, level %d\n\n", data.first, data.second);
        if (explode(data.first, data.second)) {
            printf("Explode ");
            return true;
        }
        if (split(data.first, data.second)) {
            printf("Split ");
            return true;
        }
        data = next(data.first, data.second);
    }
    printf("Nothing to do here: ");
    return false;
}

size_t count_sum(number* head) {
    size_t total = 0;
    if (head->left) {
        total += count_sum(head->left);
    }
    if (head->right) {
        total += count_sum(head->right);
    }
    if (not head->left and not head->right) {
        total += head->value;
    }
    return total;
}
size_t count_magnitude(number* node) {
    if (not node->left and not node->right) {
        return node->value;
    }
    size_t magnitude = 0;
    if (node->left) {
        magnitude += count_magnitude(node->left) * 3;
    }
    if (node->right) {
        magnitude += count_magnitude(node->right) * 2;
    }
    return magnitude;
}
number* add(number* left, number* right) {
    printf("Add ");
    print(*left);
    printf(" to ");
    print(*right);
    printf("\n");
    number* result;
    result = new number();
    result->left = left;
    result->right = right;
    left->parent = result;
    right->parent = result;
    printf("Before reduction: ");
    print(*result);
    printf("\n");
    while (reduce(result)) {
        print(*result);
        printf("  --> sum: %zu", count_sum(result));
        printf("\n");
    }
    print(*result);
    printf("\n");
    return result;
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
    size_t line_no = 0;
    std::vector<number*> numbers;
    for (string line; getline(input, line); line_no++) {
        numbers.push_back(parsing_number(line));
    }

    for (auto& n: numbers) {
        print(*n);
        printf("\n");
//        reduce(n);
//        print(*n);
//        printf("\n");
    }

    number* result = numbers.front();
    for (size_t i = 1; i < numbers.size(); i++) {
        result = add(result, numbers[i]);
    }
    printf("Result is: ");
    print(*result);
    printf("\n");
//    ::printf("Task 1 result: %" PRId64 "\n", line_no);
    printf("Task 1 result %zu\n", count_magnitude(result));
    clear(*result);
    numbers.clear();
    return 0;
}

