#include <stdio.h>
#include <stdlib.h>
struct Node{
    struct Node* prev;
    struct Node* next;
    long value;
};

struct Node* get_next_by(struct Node*, long);
struct Node* get_previous_by(struct Node*, long);
struct Node* get_new_node(long);
struct Node* remove_node(struct Node*);

void print_state(struct Node*);

long get_max_score(long*, long);


struct Node* get_new_node(long val) {
    struct Node* node = (struct Node*) calloc(sizeof(struct Node), 1);
    node->value = val;
    return node;
}

long get_max_score(long* scores, long size) {
    long max_score = 0;
    for (long i = 0; i < size; i++) {
        if (scores[i] > max_score) {
            max_score = scores[i];
        }
    }
    return max_score;
}

struct Node* get_previous_by(struct Node* current, long count) {
    if (count < 0) {
        return get_next_by(current, count * (-1));
    } else {
        for (long i = 0; i < count; i++) {
            current = current->prev;
        }
    }
    return current;
}

struct Node* get_next_by(struct Node* current, long count) {
    if (count < 0) {
        return get_previous_by(current, count * (-1));
    } else {
        for (long i = 0; i < count; i++) {
            current = current->next;
        }
    }
    return current;
}

struct Node* remove_node(struct Node* node) {
    if (node == NULL) return node;
    struct Node* temp = node;
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    long last = 0;
    node = node->next;
    if (temp->next == temp && temp->prev == temp) {
        node = NULL;
    }
    free(temp);
    return node;
}

void print_state(struct Node* state) {
    if(state == NULL) return;
    struct Node* focus = state->next;
    printf("[ %ld", state->value);
    while(focus != state) {
        printf(", %ld", focus->value);
        focus = focus->next;
    }
    printf(" ]\n");
}

int main()
{
    long player_count, marble_count;
    scanf("%ld %ld", &player_count, &marble_count);
    marble_count *= 100;
    struct Node* state = get_new_node(0);
    state->next = get_new_node(1);
    state->next->next = state;
    state->next->prev = state;
    state->prev = state->next;
    struct Node* focus = state->next;
    long last_marble = 1;
    long player_no = 1;
    long *scores = (long*)calloc(sizeof(long), player_count);
    printf("%ld, %ld\n", player_count, marble_count);
    for(long round_no = 2; round_no <= marble_count; round_no++) {
//        if (round_no % 200000 == 0) {
//            printf("Round: %ld\n", round_no);
//        }
        player_no += 1;
        player_no %= player_count;
        if (round_no % 23 != 0) {
            focus = get_next_by(focus, 2);
            struct Node* temp = get_new_node(round_no);
            temp->prev = focus->prev;
            temp->next = focus;
            temp->next->prev = temp;
            temp->prev->next = temp;
            focus = temp;
        } else {
            long temp_score = round_no;
            focus = get_previous_by(focus, 7);
            temp_score += focus->value;
            focus = remove_node(focus);
            scores[player_no] += temp_score;
        }
//        print_state(state);
    }
    printf("Result: %ld\n", get_max_score(scores, player_count));
    free(scores);
    while (state != NULL) {
        state = remove_node(state);
    }
    return 0;
}
