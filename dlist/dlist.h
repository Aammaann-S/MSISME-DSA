// Header File
// dlist.h

// Creating a singly linked list
#ifndef __INCLUDED_DLIST__ // If __INCLUDED_DLIST__ has NOT been defined, define it and include this code."
#define __INCLUDED_DLIST__
#include <stdio.h>
#include <stdint.h> // or we can use <cstdint>
// #include <list>
// for the uint32_t(unsigned), int32_t(signed) etc (fixedx size integer types)

typedef struct _node_ Node;  // helps use the "Node" directly instead of using struct _node_ every time
typedef struct _dlist_ List; // helps use the struct _dlist_ as "List" directly

/*
defines the structure of node as intended ie.
cosisting of:
1. Data and,
2. pointer to next node
The last Node will have the pointer as NULL
*/
struct _node_
{
    Node *prev;
    int32_t data;
    Node *next;
};

/*
This is the list object that will have the Nodes,
consisting of
1. head,
2. tail and,
3. the length of list(number of nodes in it)
*/
struct _dlist_
{
    /* data */
    Node *head;      // means "head" is a pointer to a "Node" (a structure defined for _node_)
    Node *tail;      // means "tail" is a pointer to a "Node" (a structure defined for _node_)
    uint32_t length; // gives the number of Nodes in the list
};

/*
The Public interface of ADT
Function declarations that tell these functions exist,
Their actual implementation will be somewhere else
Reason why the header file can expose functionality without exposing all implementation details
*/

List *dlist_new();
List *dlist_free(List *);
uint32_t dlist_length(const List *list);
uint32_t dlist_lookup(const List *list, int32_t data);
List *dlist_add_head(List *list, int32_t data);
List *dlist_add_tail(List *list, int32_t data);
List *dlist_delete_head(List *list);
List *dlist_delete_tail(List *list);

#endif
