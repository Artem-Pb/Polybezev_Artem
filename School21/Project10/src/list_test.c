#include "list.h"

#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define FAIL 1

int test_add_door() {
    struct door d1 = {1, 0};
    struct door d2 = {2, 1};
    struct door d3 = {3, 0};

    struct Node* head = init(&d1);
    if (head == NULL) return FAIL;

    const struct Node* new_node = add_door(head, &d2);
    if (new_node == NULL) {
        destroy(&head);
        return FAIL;
    }

    new_node = add_door(head->next, &d3);
    if (new_node == NULL) {
        destroy(&head);
        return FAIL;
    }

    if (head->id != 1 || head->next->id != 2 || head->next->next->id != 3 || head->next->next->next != NULL) {
        destroy(&head);
        return FAIL;
    }

    destroy(&head);
    return SUCCESS;
}

int test_remove_door() {
    struct door d1 = {1, 0};
    struct door d2 = {2, 1};
    struct door d3 = {3, 0};

    struct Node* head = init(&d1);
    if (head == NULL) return FAIL;

    const struct Node* new_node = add_door(head, &d2);
    if (new_node == NULL) {
        destroy(&head);
        return FAIL;
    }

    new_node = add_door(head->next, &d3);
    if (new_node == NULL) {
        destroy(&head);
        return FAIL;
    }

    const struct Node* node_to_remove = find_door(2, head);
    if (node_to_remove == NULL) {
        destroy(&head);
        return FAIL;
    }

    head = remove_door(node_to_remove, &head);
    if (head == NULL) {
        destroy(&head);
        return FAIL;
    }

    if (head->id != 1 || head->next->id != 3 || head->next->next != NULL) {
        destroy(&head);
        return FAIL;
    }

    destroy(&head);
    return SUCCESS;
}

int main() {
    int result_add = test_add_door();
    int result_remove = test_remove_door();

    printf("%s\n", (result_add == SUCCESS ? "SUCCESS" : "FAIL"));
    printf("%s\n", (result_remove == SUCCESS ? "SUCCESS" : "FAIL"));

    return 0;
}