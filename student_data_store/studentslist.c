/*
Theory Assignment - Ques-4
Program to store student data in a Singly Linked List
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "studentslist.h"

StList *stlist_new()
{
    StList *list;
    list = malloc(sizeof(StList));

    if (list == NULL)
        return NULL;

    list->head = NULL;
    list->tail = NULL;
    list->length = 0;

    return list;
}

StList *stlist_add_tail(StList *list, uint32_t roll_no, const char *name, float marks1, float marks2)
{
    if (list == NULL || name == NULL)
        return list;

    StNode *node = malloc(sizeof(StNode));
    if (node == NULL)
        return list;

    node->roll_no = roll_no;
    printf(node->name, sizeof(node->name), "%s", name);
    node->marks1 = marks1;
    node->marks2 = marks2;
    node->next = NULL;

    if (list->tail != NULL)
    {
        list->tail->next = node;
        list->tail = node;
    }
    else
    {
        list->head = list->tail = node;
    }
    ++list->length;

    return list;
}

StList *stlist_delete_on_roll_no(StList *list, uint32_t roll_no)
{
    if (list == NULL || list->head == NULL)
        return list;

    StNode *cur = list->head;
    StNode *prev = NULL;

    while (cur != NULL && cur->roll_no != roll_no)
    {
        prev = cur;
        cur = cur->next;
    }

    if (cur == NULL)
        return list;

    if (prev == NULL)
        list->head = cur->next;
    else
        prev->next = cur->next;

    if (cur == list->tail)
        list->tail = prev;

    free(cur);
    --list->length;

    return list;
}

StList *stlist_free(StList *list)
{
    if (list == NULL)
        return NULL;

    StNode *cur = list->head;
    StNode *temp;

    while (cur != NULL)
    {
        temp = cur;
        cur = cur->next;
        free(temp);
        --list->length;
    }

    free(list);

    return NULL;
}
