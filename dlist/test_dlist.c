#include <stdio.h>
#include <assert.h>
#include "dlist.h"

void display(List *list)
{
    Node *cur = list->head;

    while (cur != NULL)
    {
        printf("%d ", cur->data);
        cur = cur->next;
    }

    printf("\n");
}

void test_dlist(void)
{
    List *list = dlist_new();

    assert(list != NULL);
    assert(dlist_length(list) == 0);

    /* Test insertion at head and tail */
    list = dlist_add_head(list, 20);
    list = dlist_add_head(list, 10);
    list = dlist_add_tail(list, 30);
    list = dlist_add_tail(list, 40);

    printf("After insertion: ");
    display(list);

    assert(dlist_length(list) == 4);
    assert(list->head->data == 10);
    assert(list->tail->data == 40);

    /* Test forward and backward links */
    assert(list->head->next->data == 20);
    assert(list->head->next->prev == list->head);
    assert(list->tail->prev->data == 30);
    assert(list->tail->prev->next == list->tail);

    /* Test lookup */
    assert(dlist_lookup(list, 20) == 1);
    assert(dlist_lookup(list, 99) == 0);

    /* Test insertion after a given value */
    list = dlist_add_on_data(list, 20, 25);

    printf("After inserting 25: ");
    display(list);

    assert(dlist_length(list) == 5);
    assert(list->head->next->next->data == 25);
    assert(list->head->next->next->prev->data == 20);

    /* Test deletion of a given value */
    list = dlist_delete_on_data(list, 25);

    printf("After deleting 25: ");
    display(list);

    assert(dlist_length(list) == 4);

    /* Test deletion at head */
    list = dlist_delete_head(list);

    printf("After deleting head: ");
    display(list);

    assert(list->head->data == 20);
    assert(list->head->prev == NULL);

    /* Test deletion at tail */
    list = dlist_delete_tail(list);

    printf("After deleting tail: ");
    display(list);

    assert(list->tail->data == 30);
    assert(list->tail->next == NULL);
    assert(dlist_length(list) == 2);

    /* Deleting a value that does not exist */
    list = dlist_delete_on_data(list, 99);
    assert(dlist_length(list) == 2);

    /* Test deleting all remaining nodes */
    list = dlist_delete_head(list);
    list = dlist_delete_tail(list);

    assert(list->head == NULL);
    assert(list->tail == NULL);
    assert(dlist_length(list) == 0);

    /* Free the list */
    list = dlist_free(list);
    assert(list == NULL);

    printf("All doubly linked list tests passed!\n");
}

int main(void)
{
    test_dlist();
    return 0;
}
