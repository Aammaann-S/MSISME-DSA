// Header File
// slist.h

// Creating a singly linked list
#ifndef __INCLUDED_SLIST__ // If __INCLUDED_SLIST__ has NOT been defined, define it and include this code."
#define __INCLUDED_SLIST__
#include <stdio.h>
#include <stdint.h> // or we can use <cstdint>
// #include <list>
// for the uint32_t(unsigned), int32_t(signed) etc (fixedx size integer types)

typedef struct _node_ Node;  // helps use the "Node" directly instead of using struct _node_ every time
typedef struct _slist_ List; // helps use the struct _slist_ as "List" directly

/*
defines the structure of node as intended ie.
cosisting of:
1. Data and,
2. pointer to next node
The last Node will have the pointer as NULL
*/
struct _node_
{
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
struct _slist_
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

List *slist_new();
List *slist_free(List *);
uint32_t slist_length(const List *list);
uint32_t slist_lookup(const List *list, int32_t data);
List *slist_add_head(List *list, int32_t data);
List *slist_add_tail(List *list, int32_t data);
List *slist_delete_head(List *list);
List *slist_delete_tail(List *list);

// Lab Assiginment - Ques-4
int32_t slist_get_min(const List *list);
int32_t slist_get_max(const List *list);

#endif
