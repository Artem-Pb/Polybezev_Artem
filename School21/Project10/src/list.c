#include "list.h"

struct Node* init(const struct door* door) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    if (node == NULL) return NULL;

    node->id = door->id;
    node->status = door->status;
    node->next = NULL;

    if (node->id < 0 || (node->status != 0 && node->status != 1)) {
        free(node);
        return NULL;
    }

    return node;
}

struct Node* add_door(struct Node* prev_node, const struct door* door) {
    if (prev_node == NULL || door == NULL) return NULL;

    if (door->id < 0 || (door->status != 0 && door->status != 1)) return NULL;

    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    if (node == NULL) return NULL;

    node->id = door->id;
    node->status = door->status;

    node->next = prev_node->next;
    prev_node->next = node;

    return node;
}

struct Node* find_door(int door_id, struct Node* root) {
    if (root == NULL) return NULL;

    struct Node* current = root;
    while (current != NULL) {
        if (current->id == door_id) return current;
        current = current->next;
    }

    return NULL;
}

struct Node* remove_door(const struct Node* elem, struct Node** root) {
    if (*root == NULL || elem == NULL) return NULL;

    struct Node* current = *root;
    struct Node* prev = NULL;

    if (current->id == elem->id) {
        *root = current->next;
        free(current);
        return *root;
    }

    while (current != NULL && current->id != elem->id) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) return *root;

    prev->next = current->next;
    free(current);

    return *root;
}

void destroy(struct Node** root) {
    struct Node* current = *root;
    struct Node* next_node;

    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }

    *root = NULL;
}
