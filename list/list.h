#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>

typedef int64_t list_data_t;

typedef struct node {
    list_data_t data;
    struct node *next;
    struct node *prev;
} node_t;

#define POIZON_VAL -1

node_t *list_create_node(list_data_t new_data);
node_t *list_ctor(size_t size);