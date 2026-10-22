// dlist.c
#include <stdio.h>
#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include "dlist.h"

List *dlist_new()
{
    List *list;
    list = malloc(sizeof(List));

    if (list == NULL)
        return NULL;

    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
    return list;
}

// Purpose : delete the entire linked list and release its memory
List *dlist_free(List *list)
{
    if (list == NULL)
        return NULL;

    Node *cur, *p;

    if (dlist_length(list) > 0)
    {
        assert(list->head && list->tail);
        cur = list->head;
        list->head = NULL;
        list->tail = NULL;

        while (cur != NULL)
        {
            p = cur;
            cur = cur->next;
            free(p);
            --list->length;
        }
    }
    free(list);

    return NULL;
}

/*
Helper internal function to allocate node that hold data
Creates a new Node and initializes iut with data
the head of list will point to the new node
*/
static Node *__list_node_new__(int32_t data)
{
    Node *node = malloc(sizeof(Node));

    if (node == NULL)
        return NULL;

    node->prev = NULL;
    node->data = data;
    node->next = NULL;

    return node;
}

List *dlist_add_head(List *list, int32_t data)
{
    if (list == NULL)
        return NULL;

    Node *node = __list_node_new__(data);
    node->next = list->head;

    if (list->head != NULL)
        list->head->prev = node;
    else
        list->tail = node;
    list->head = node;
    ++list->length;

    assert((list->length == 1 && list->head == list->tail) || (list->length > 0 && list->head != list->tail));
    return list;
}

uint32_t dlist_length(const List *list)
{
    return list->length;
}

uint32_t dlist_lookup(const List *list, int32_t key)
{
    Node *node = list->head;
    for (node = list->head; node != NULL; node = node->next)
    {
        if (node->data == key)
        {
            break;
        }
    }
    return (node != NULL); // gives true(1)/false(0)
}

List *dlist_add_tail(List *list, int32_t data)
{
    if (list == NULL)
        return NULL;

    Node *node = __list_node_new__(data);
    node->prev = list->tail;

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

List *dlist_delete_head(List *list)
{
    if (list == NULL)
        return NULL;

    if (list->head != NULL)
    {
        Node *node;
        node = list->head;
        assert(list->length > 0);
        list->head = list->head->next;
        --list->length;
        if (list->head == NULL)
        {
            list->tail = NULL;
            assert(list->length == 0);
        }
        else
        {
            list->head->prev = NULL;
        }
        free(node);
    }
    return list;
}

List *dlist_delete_tail(List *list)
{
    assert(list != NULL);
    if (list == NULL)
        return NULL;

    if (list->tail != NULL)
    {
        Node *tail = list->tail;
        assert(list->length > 0);
        if (list->tail == list->head)
        {
            list->head = list->tail = NULL;
        }
        else
        {
            list->tail = list->tail->prev;
            list->tail->next = NULL;
        }
        free(tail);
        --list->length;
    }
    return list;
}

List *dlist_add_on_data(List *list, int32_t key, int32_t data)
{
    if (list == NULL)
        return NULL;

    Node *cur = list->head;

    while (cur != NULL && cur->data != key)
        cur = cur->next;

    if (cur == NULL)
        return list;

    Node *node = __list_node_new__(data);

    if (node == NULL)
        return list;

    node->prev = cur;
    node->next = cur->next;

    if (cur->next != NULL)
        cur->next->prev = node;
    else
        list->tail = node;

    cur->next = node;
    ++list->length;

    return list;
}

List *dlist_delete_on_data(List *list, int32_t data)
{
    if (list == NULL)
        return NULL;

    Node *cur = list->head;

    while (cur != NULL && cur->data != data)
        cur = cur->next;

    if (cur == NULL)
        return list;

    if (cur->prev != NULL)
        cur->prev->next = cur->next;
    else
        list->head = cur->next;

    if (cur->next != NULL)
        cur->next->prev = cur->prev;
    else
        list->tail = cur->prev;

    free(cur);
    --list->length;

    return list;
}
