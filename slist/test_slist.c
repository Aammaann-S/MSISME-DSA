
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "slist.h"

void test_slist_generic(void)
{
    List *list = slist_new();

    assert(list != NULL);
    assert(slist_length(list) == 0);

    /* Insert at head */
    slist_add_head(list, 10);
    slist_add_head(list, 20);

    assert(slist_length(list) == 2);
    assert(slist_lookup(list, 20));
    assert(slist_lookup(list, 10));
    assert(!slist_lookup(list, 99));

    /* Insert at tail */
    slist_add_tail(list, 30);
    slist_add_tail(list, 40);

    assert(slist_length(list) == 4);
    assert(slist_lookup(list, 30));
    assert(slist_lookup(list, 40));

    /* Insert another node at head */
    slist_add_head(list, 5);

    assert(slist_length(list) == 5);

    /* Delete head */
    slist_delete_head(list);

    assert(slist_length(list) == 4);
    assert(!slist_lookup(list, 5));

    /* Delete tail */
    slist_delete_tail(list);

    assert(slist_length(list) == 3);
    assert(!slist_lookup(list, 40));

    /* Reverse the list */
    slist_reverse(list);

    assert(list->head->data == 30);
    assert(list->tail->data == 10);

    /* Free the list */
    list = slist_free(list);

    /*
       If slist_free() frees the List structure
       and returns NULL, this assertion is valid.
    */
    assert(list == NULL);

    printf("SList tests passed!\n");
}

int main(void)
{
    test_slist_generic();
    return 0;
}
