
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "slist.h"

/*
Lab Assignment - Ques-5
Delete duplicate elements
*/
void test_delete_duplicates(void)
{
    List *list = slist_new();
    assert(list != NULL);

    slist_add_tail(list, 10);
    slist_add_tail(list, 20);
    slist_add_tail(list, 10);
    slist_add_tail(list, 30);
    slist_add_tail(list, 20);

    slist_delete_duplicates(list);

    /* Expected list: 10 -> 20 -> 30 */
    assert(slist_length(list) == 3);
    assert(list->head->data == 10);
    assert(list->head->next->data == 20);
    assert(list->tail->data == 30);
    assert(list->tail->next == NULL);

    slist_free(list);
}

/* Find the middle node */
void test_middle(void)
{
    List *list = slist_new();
    assert(list != NULL);

    slist_add_tail(list, 10);
    slist_add_tail(list, 20);
    slist_add_tail(list, 30);
    slist_add_tail(list, 40);
    slist_add_tail(list, 50);

    Node *middle = slist_middle(list);

    assert(middle != NULL);
    assert(middle->data == 30);

    slist_free(list);
}

/* Check whether a cycle exists */
void test_check_cycle(void)
{
    List *list = slist_new();
    assert(list != NULL);

    slist_add_tail(list, 10);
    slist_add_tail(list, 20);
    slist_add_tail(list, 30);

    /* A normal list has no cycle */
    assert(slist_check_cycle(list) == 0);

    /* Create a cycle: last node points to head */
    list->tail->next = list->head;

    assert(slist_check_cycle(list) == 1);

    /* Break the cycle before freeing the list */
    list->tail->next = NULL;

    slist_free(list);
}

/* Get a node at a position */
void test_get_on_position(void)
{
    List *list = slist_new();
    assert(list != NULL);

    slist_add_tail(list, 10);
    slist_add_tail(list, 20);
    slist_add_tail(list, 30);

    /* Positions are 1-based */
    Node *node = slist_get_on_position_V2(list, 2);
    assert(node != NULL);
    assert(node->data == 20);

    /* Invalid positions */
    assert(slist_get_on_position_V2(list, 0) == NULL);
    assert(slist_get_on_position_V2(list, 4) == NULL);

    slist_free(list);
}

/* Remove a node at a position */
void test_remove_on_position(void)
{
    List *list = slist_new();
    assert(list != NULL);

    slist_add_tail(list, 10);
    slist_add_tail(list, 20);
    slist_add_tail(list, 30);
    slist_add_tail(list, 40);

    /* Remove position 2: 10 -> 30 -> 40 */
    slist_remove_on_position_V2(list, 2);

    assert(slist_length(list) == 3);
    assert(list->head->data == 10);
    assert(list->head->next->data == 30);
    assert(list->tail->data == 40);

    /* Remove the head */
    slist_remove_on_position_V2(list, 1);
    assert(slist_length(list) == 2);
    assert(list->head->data == 30);

    /* Remove the tail */
    slist_remove_on_position_V2(list, 2);
    assert(slist_length(list) == 1);
    assert(list->head->data == 30);
    assert(list->tail == list->head);

    /* Remove the only remaining node */
    slist_remove_on_position_V2(list, 1);
    assert(slist_length(list) == 0);
    assert(list->head == NULL);
    assert(list->tail == NULL);

    /* Invalid position should leave the empty list unchanged */
    slist_remove_on_position_V2(list, 1);
    assert(slist_length(list) == 0);

    slist_free(list);
}

int main(void)
{
    test_delete_duplicates();
    test_middle();
    test_check_cycle();
    test_get_on_position();
    test_remove_on_position();

    printf("All Q5 SList tests passed!\n");

    return 0;
}
