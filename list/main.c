#include "list.h"

int main() {
    node_t *head = list_ctor(10);
    for (size_t i = 0; i != 9; ++i) {
        printf("<%d>\t", head->data);
        printf("<%p>\t", head);
        printf("<%p>\t", head->next);
        printf("\n");
        if(head->next != NULL)
            head = head->next;
    }
}