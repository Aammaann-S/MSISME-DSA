// slist.c
#include <stdio.h>
#include <stddef.h>
#include <assert.h>
#include <stdlib.h> // need this for malloc?
#include "slist.h"

List *slist_new()
{
    List *list; // list is a pointer // this only creates a pointer List object not created yet
    // list = (List *)malloc(sizeof(list));
    list = malloc(sizeof(List)); // or it can be : malloc(sizeof *list)
    // gives the size of the pointer not size of List structure
    // malloc alllocates memory?
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
    return list;
}

// Purpose : delete the entire linked list and release its memory
List *slist_free(List *list)
{

    Node *cur, *p; // temporary pointers

    if (slist_length(list) > 0)
    {
        assert(list->head && list->tail);
        // if the condition inside assert is not true the program terminates and reports an assertion failure

        cur = list->head;
        // setting to NULL sybolizing the list no longer points to any nodes
        list->head = NULL;
        list->tail = NULL;

        while (cur != NULL)
        {
            p = cur;
            cur = cur->next;
            free(p);
            --list->length; // after deletion of a node this part decreses the length
        }
    }
    return list;
}

/*
Helper internal function to allocate node that hold data
Creates a new Node and initializes iut with data
the head of list will point to the new node
*/
static Node *__list_node_new__(int32_t data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

List *slist_add_head(List *list, int32_t data)
{
    Node *node = __list_node_new__(data);
    node->next = list->head;
    list->head = node;

    // first node in the list
    if (list->tail == NULL)
    {
        list->tail = node;
    }
    ++list->length;

    assert(
        (list->length == 1 && list->head == list->tail) ||
        (list->length > 0 && list->head != list->tail));
    return list;
}

uint32_t slist_length(const List *list)
{
    return list->length;
}

uint32_t slist_lookup(const List *list, int32_t key)
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

List *slist_add_tail(List *list, int32_t data)
{
    Node *node = __list_node_new__(data);
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

List *slist_delete_head(List *list)
{
    Node *node;
    if (list->head != NULL)
    {
        assert(list->length > 0);
        node = list->head;
        list->head = list->head->next;
        --list->length;
        if (list->head == NULL)
        {
            list->tail = NULL;
            assert(list->length == 0);
        }
        free(node); // free/delete previos head in temporary node
    }
    return list;
}

List *slist_delete_tail(List *list)
{
    assert(list != NULL);
    Node *tail = list->tail;
    Node *node;
    if (list->tail != NULL)
    {
        assert(list->length > 0);
        if (list->tail == list->head)
        {
            list->head = list->tail = NULL;
        }
        else // Find the node till one step behid the tail node
        {
            for (node = list->head; node->next != list->tail; node = node->next)
                ;
            list->tail = node;
            list->tail->next = NULL;
            free(tail);
        }
        --list->length;
    }
    return list;
}
