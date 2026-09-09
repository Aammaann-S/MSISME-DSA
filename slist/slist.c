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

uint32_t slist_length(const List *list)
{
    return list->length;
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
        // setting to NULL sybolizing the list vars(head, tail) no longer points to any nodes
        list->head = NULL;
        list->tail = NULL;

        while (cur != NULL)
        {
            p = cur;
            cur = cur->next;
            free(p);
            --list->length; // after deletion of a(each) node this part decreses the length
        }
    }
    return list;
}

/*
Helper internal function to allocate node that hold data
*/
static Node *__list_node_new__(int32_t data)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

/*
Creates a new Node and initializes it with data
the head of list will point to the new node
*/
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
        else // Find the node till one step behind the tail node
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

List *slist_add_on_data(List *list, int32_t key, int32_t data)
{
    if (list->head != NULL)
    {
        Node *cur = list->head;
        Node *node = __list_node_new__(data);
        for (; cur != NULL && cur->data != key; cur = cur->next)
            ;
        if (cur != NULL)
        {
            node->next = cur->next;
            cur->next = node;
            if (node->next == NULL)
            {
                list->tail = node;
            }
        }
        ++list->length;
    }
    return list;
}

List *slist_delete_on_data(List *list, int32_t data)
{
    if (list->head != NULL)
    {
        Node *cur, *p;
        cur = list->head;
        // deleting the head node if "data" match
        if (cur->data == data)
        {
            list->head = cur->next;
        }
        else
        {
            p = cur;
            cur = cur->next;
            while (cur != NULL)
            {
                if (cur->data == data)
                {
                    p->next = cur->next;
                }
                else
                {
                    p = cur;
                    cur = cur->next;
                }
            }
            if (cur == list->tail)
            {
                list->tail = p;
            }
        }
        if (list->head == NULL)
        {
            list->tail = NULL;
        }
        free(cur);
        --list->length;
    }
}

/*
Ques -
Code to find the largest and smallest in the given Linked List
*/

List *slist_reverse(List *list)
{
    Node *prev = NULL;
    Node *current = list->head;
    Node *next = NULL;

    list->tail = list->head; // points to the first

    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    list->head = prev; // point to end
    return list;
}

/*
Ques-
Find nth element from end after reversing the slist
*/

/*
Ques-
Delete all duplicate elements from SList
Sol-
Compare the 1st element with all rest elements one by one > delete any matching you find > then iterate from teh 1st element to 2nd, repeat and so on.
*/

/*
Ques-
Find the middle node of the slist
*/

/*
Ques-
Check if a cycle exists in the slist
*/
List *slist_check_cycle(List *list)
{
    // Node *slow = *head;
    // Node *fast = *head;
    Node *slow = list->head;
    Node *fast = list->head;

    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast)
        {
            return 1; // Cycle detected
        }
    }
    return 0;
}

/*
Ques-
Program to store student data in a Singly Linked List
*/

/*
Program to return an element att a given position in a Singly Linked List
*/
Node *slist_get_on_position(List *list, int32_t pos)
{
    Node *temp = list->head;
    int32_t count = 1;
    assert(list->length >= pos);
    while (count != pos)
    {
        temp = temp->next;
        count++;
    }
    return temp;
}

/*
Assiginment -
Program to remove an element at a given position in a Singly Linked List
*/
List *slist_remove_on_position(List *list, int32_t pos)
{
    if (list->head != NULL)
    {

        Node *cur = list->head;
        Node *prev;
        int32_t count = 1;
        assert(list->length > 0);

        // deleting the head node if "pos" matches
        if (count == pos)
        {
            list->head = cur->next;
        }
        // otherwise test others
        else
        {
            prev = cur; // temp previous
            cur = cur->next;
            while (count != pos)
            {
                if (count == pos)
                {
                    prev = cur->next;
                }
                prev = cur;
                cur = cur->next;
                count++;
            }
            if (cur == list->tail)
            {
                list->tail = prev;
            }
        }
        if (list->head == NULL)
        {
            list->tail = NULL;
        }

        free(cur);
        --list->length;
    }
}

/*
Assiginment -
Program to Write program to find the union and intersection of 2 Singly Linked Lists. The resultant list elements should be unique
*/

/*
Assiginment -
Program to compare 2 Singly Linked Lists, find the difference between the 2 singly linked lists
*/

/*
Assiginment -
Program for Implementing STACK using singly linked lists
*/

// // List *stack_add(List *list, int32_t item)
// void *stack_add(List *list, int32_t item)
// {

//     Node *temp = __list_node_new__(item);
//     if (temp != NULL)
//     {
//         temp->next = list->head;
//         list->head = temp;
//         // return true;
//     }
//     else
//     {
//         printf("Stack Out of Space");
//         // return false;
//     }
// }

// // List *stack_add(List *list, int32_t item)
// void *stack_delete(List *list)
// {

//     Node *temp = list->head;
//     if (list->head = NULL)
//     {
//         printf("Stack Empty");
//         // return false;
//     }
//     else
//     {
//         item = temp->data;
//         list->head = temp->next;
//         slist_delete_head(list);
//         // return true;
//     }
// }
