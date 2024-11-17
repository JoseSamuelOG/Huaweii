#include "list.h"

node_t *list_create_node(list_data_t new_data) {
    node_t *new_node = (node_t *)calloc(1, sizeof(node_t));

    new_node->data = new_data;
    new_node->next = NULL;
    new_node->prev = NULL;

    return new_node;
}

node_t *list_ctor(size_t size) {
    node_t *head = list_create_node(POIZON_VAL);
    for (size_t i = 0; i != size; ++i) {
        node_t *new_node = list_create_node(POIZON_VAL);
        new_node->prev = head;
        head->next = new_node;
        head = new_node;
    }
}