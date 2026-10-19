// Header File
// dlist.h

// Creating a Doubly linked list
#ifndef __INCLUDED_DLLIST__
#define __INCLUDED_DLLIST__
#include <stdio.h>
#include <stdint.h>

typedef struct _node_ Node;
typedef struct _dlist_ List;

struct _node_
{
    Node *prev;
    int32_t data;
    Node *next;
};

struct _dlist_
{
    Node *head;
    Node *tail;
    uint32_t length;
};

List *dlist_new();
List *dlist_free(List *);
uint32_t dlist_length(const List *list);
uint32_t dlist_lookup(const List *list, int32_t data);
List *dlist_add_head(List *list, int32_t data);
List *dlist_add_tail(List *list, int32_t data);
List *dlist_delete_head(List *list);
List *dlist_delete_tail(List *list);
List *dlist_add_on_data(List *list, int32_t key, int32_t data);
List *dlist_delete_on_data(List *list, int32_t data);

#endif
