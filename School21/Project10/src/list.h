#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

struct door {
    int id;
    int status;
};

struct Node {
    int id;
    int status;
    struct Node* next;
};

struct Node* init(const struct door* door);
struct Node* add_door(struct Node* prev_node, const struct door* door);
struct Node* find_door(int door_id, struct Node* root);
struct Node* remove_door(const struct Node* elem, struct Node** root);
void destroy(struct Node** root);

#endif
