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

// Lab Assignment - Ques-4
int32_t slist_get_min_value(const List *list);
int32_t slist_get_max_value(const List *list);

List *slist_new();
uint32_t slist_length(const List *list);
List *slist_free(List *);
uint32_t slist_lookup(const List *list, int32_t data);
List *slist_add_head(List *list, int32_t data);

// Updated for : Lab Assignment - Ques-4
List *slist_add_tail(List *list, int32_t data);
List *slist_delete_head(List *list);
List *slist_delete_tail(List *list);
List *slist_add_on_data(List *list, int32_t key, int32_t data);
List *slist_delete_on_data(List *list, int32_t data);
int32_t slist_largest(List *list);
int32_t slist_smallest(List *list);
List *slist_reverse(List *list);
int32_t slist_nth_from_end(List *list, int32_t n);

// Lab Assignment - Ques-5
List *slist_delete_duplicates(List *list);
Node *slist_middle(List *list);
int slist_check_cycle(List *list);
Node *slist_get_on_position_V2(List *list, int32_t pos);
List *slist_remove_on_position(List *list, int32_t pos);
List *slist_remove_on_position_V2(List *list, int32_t pos);

// Theory Assignment - Ques-3
List *slist_union(List *list_1, List *list_2);
List *slist_intersection(List *list_1, List *list_2);

List *slist_difference(List *a, List *b);
int slist_compare(List *a, List *b);

// Task - Stack via SLL
List *stack_push(List *stack, int32_t item);
int stack_pop(List *stack, int32_t *item);
int stack_peek(List *stack, int32_t *item);

#endif
