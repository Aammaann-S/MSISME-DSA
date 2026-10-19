#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include "studentslist.h"

void test_studentslist_generic(void)
{
    StList *list = stlist_new();

    assert(list != NULL);
    assert(list->length == 0);
    assert(list->head == NULL);
    assert(list->tail == NULL);

    /* Insert student records */
    stlist_add_tail(list, 101, "Aman", 85.5f, 90.0f);
    stlist_add_tail(list, 102, "Riya", 92.0f, 88.5f);
    stlist_add_tail(list, 103, "Rahul", 78.0f, 81.5f);

    assert(list->length == 3);
    assert(list->head->roll_no == 101);
    assert(strcmp(list->head->name, "Aman") == 0);
    assert(list->tail->roll_no == 103);

    /* Check marks */
    assert(list->head->marks1 == 85.5f);
    assert(list->head->marks2 == 90.0f);

    /* Delete the middle student */
    stlist_delete_on_roll_no(list, 102);

    assert(list->length == 2);
    assert(list->head->roll_no == 101);
    assert(list->head->next->roll_no == 103);
    assert(list->tail->roll_no == 103);

    /* Delete the head student */
    stlist_delete_on_roll_no(list, 101);

    assert(list->length == 1);
    assert(list->head->roll_no == 103);
    assert(list->tail->roll_no == 103);

    /* Delete the last remaining student */
    stlist_delete_on_roll_no(list, 103);

    assert(list->length == 0);
    assert(list->head == NULL);
    assert(list->tail == NULL);

    /* Test deleting from an empty list */
    stlist_delete_on_roll_no(list, 999);
    assert(list->length == 0);

    /* Free the list */
    list = stlist_free(list);

    assert(list == NULL);

    printf("Student list tests passed!\n");
}

int main(void)
{
    test_studentslist_generic();
    return 0;
}
