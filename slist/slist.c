// slist.c
#include <stdio.h>
#include <stddef.h>
#include <assert.h>
#include <stdlib.h> // need this for malloc?
#include "slist.h"

// Lab Assiginment - Ques-4
static int32_t min_value = INT32_MAX;
static int32_t max_value = INT32_MIN;

int32_t slist_get_min(const List *list)
{
    if (list == NULL || list->length == 0)
        return 0;

    return min_value;
}

int32_t slist_get_max(const List *list)
{
    if (list == NULL || list->length == 0)
        return 0;

    return max_value;
}

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

/*
Free the node list free/ freeze the memory allocated for each node& for the linked list structure itself.
the list descripter lives on till the list destroy function is called
*/
// Purpose : delete the entire linked list and release its memory
List *slist_free(List *list)
{

    Node *cur, *temp; // temporary pointers

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
            temp = cur;
            cur = cur->next;
            free(temp);
            --list->length; // after deletion of a(each) node this part decreses the length
        }
    }
    free(list);
    return NULL;
    // return list;
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

// List *slist_add_tail(List *list, int32_t data)
// {
//     Node *node = __list_node_new__(data);
//     if (list->tail != NULL)
//     {
//         list->tail->next = node;
//         list->tail = node;
//     }
//     else
//     {
//         list->head = list->tail = node;
//     }
//     ++list->length;
//     return list;
// }

// Updated for :
// Lab Assiginment - Ques-4
List *slist_add_tail(List *list, int32_t data)
{
    if (list == NULL)
        return NULL;
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

    if (list->length == 0)
    {
        min_value = data;
        max_value = data;
    }
    else
    {
        if (data < min_value)
            min_value = data;

        if (data > max_value)
            max_value = data;
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
            ++list->length;
        }
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
Task -
Code to find the largest and smallest in the given Linked List
(Bubble Sort Approach)
*/
int32_t slist_largest(List *list)
{
    assert(list != NULL);
    assert(list->head != NULL);

    int32_t largest = list->head->data;
    Node *temp = list->head;

    while (temp != NULL)
    {
        if (temp->data > largest)
            largest = temp->data;

        temp = temp->next;
    }
    return largest;
}

int32_t slist_smallest(List *list)
{
    assert(list != NULL);
    assert(list->head != NULL);

    int32_t smallest = list->head->data;
    Node *temp = list->head;

    while (temp != NULL)
    {
        if (temp->data < smallest)
            smallest = temp->data;

        temp = temp->next;
    }
    return smallest;
}

List *slist_reverse(List *list)
{
    if (list == NULL)
        return NULL;

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
Find nth element from end after reversing the slist (Theory Ass Ques-5)
*/
int32_t slist_nth_from_end(List *list, int32_t n)
{
    Node *temp;

    assert(list != NULL);
    assert(n > 0);
    assert(n <= list->length);

    slist_reverse(list);

    int32_t pos = ((list->length) - n + 1);
    temp = slist_get_on_position(list, pos);
    return temp->data;
}

/*
Lab Assiginment - Ques-5
Delete all duplicate elements from SList
Sol-
Compare the 1st element (current) with all rest elements one by one > delete any matching you find > then iterate current from the 1st element to 2nd, repeat and so on.
*/
List *slist_delete_duplicates(List *list)
{
    if (list == NULL || list->head == NULL)
        return list;

    Node *current = list->head;

    while (current != NULL)
    {
        Node *prev = current;
        Node *temp = current->next;
        while (temp != NULL)
        {
            if (temp->data == current->data)
            {
                prev->next = temp->next;
                if (temp == list->tail)
                    list->tail = prev;
                free(temp);
                temp = prev->next;
                list->length--;
            }
            else
            {
                prev = temp;
                temp = temp->next;
            }
        }
        current = current->next;
    }

    return list;
}

/*
Task-
Find the middle node of the slist
*/
Node *slist_middle(List *list)
{
    if (list == NULL)
        return NULL;

    Node *slow = list->head;
    Node *fast = list->head;

    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    // logic - slow reaches middle when fast reaches end

    return slow;
}

/*
Task-
Check if a cycle exists in the slist
*/
List *slist_check_cycle(List *list)
{
    if (list == NULL)
        return 0;

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
Program to return an element at a given position in a Singly Linked List
*/
Node *slist_get_on_position(List *list, int32_t pos)
{
    assert(list->length >= pos);

    int32_t count = 1;
    Node *temp = list->head;

    while (count != pos)
    {
        temp = temp->next;
        count++;
    }
    return temp;
}

Node *slist_get_on_position_V2(List *list, int32_t pos)
{
    if (list == NULL || pos < 1 || (uint32_t)pos > list->length)
        return NULL;

    Node *temp = list->head;

    for (int32_t i = 1;
         i < pos;
         //  i++
         i++, temp = temp->next)
        ;
    // temp = temp->next;
    return temp;
}

/*
Task -
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

List *slist_remove_on_position_V2(List *list, int32_t pos)
{
    if (list == NULL || pos < 1 ||
        (uint32_t)pos > list->length)
        return list;

    Node *temp = list->head;

    if (pos == 1)
    {
        list->head = temp->next;
        if (list->head == NULL)
            list->tail = NULL;
        free(temp);
        list->length--;
        return list;
    }

    Node *prev = list->head;
    for (int32_t i = 1;
         i < pos - 1;
         //  i++
         i++, temp = temp->next)
        ;
    // prev = prev->next;

    temp = prev->next;
    prev->next = temp->next;
    if (temp == list->tail)
        list->tail = prev;
    free(temp);
    list->length--;

    return list;
}

/*
Theory Assiginment - Ques-3
Program to Write program to find the union and intersection of 2 Singly Linked Lists. The resultant list elements should be unique
*/
List *slist_union(List *list_1, List *list_2)
{
    if (list_1 == NULL || list_2 == NULL)
        return NULL;

    Node *temp;
    List *result = slist_new();

    for (temp = list_1->head; temp != NULL; temp = temp->next)
    {
        if (slist_lookup(result, temp->data) == 0)
            slist_add_tail(result, temp->data);
    }
    for (temp = list_2->head; temp != NULL; temp = temp->next)
    {
        if (slist_lookup(result, temp->data) == 0)
            slist_add_tail(result, temp->data);
    }
    return result;
}

List *slist_intersection(List *list_1, List *list_2)
{
    if (list_1 == NULL || list_2 == NULL)
        return NULL;

    Node *temp;
    List *result = slist_new();

    for (temp = list_1->head; temp != NULL; temp = temp->next)
    {
        if (slist_lookup(list_2, temp->data) != 0 &&
            slist_lookup(result, temp->data) == 0)
        {
            slist_add_tail(result, temp->data);
        }
    }
    return result;
}

/*
Task -
Program to compare 2 Singly Linked Lists, find the difference between the 2 singly linked lists
*/
List *slist_difference(List *a, List *b)
{
    if (a == NULL || b == NULL)
        return NULL;

    List *result = slist_new();

    if (result == NULL)
        return NULL;

    Node *temp;

    for (temp = a->head; temp != NULL; temp = temp->next)
    {
        if (slist_lookup(b, temp->data) == 0 &&
            slist_lookup(result, temp->data) == 0)
        {
            slist_add_tail(result, temp->data);
        }
    }
    return result;
}

int slist_compare(List *a, List *b)
{
    if (a == NULL || b == NULL)
        return a == b;

    if (a->length != b->length)
        return 0;

    Node *p = a->head;
    Node *q = b->head;

    while (p != NULL && q != NULL)
    {
        if (p->data != q->data)
            return 0;

        p = p->next;
        q = q->next;
    }
    return 1;
}

/*
Task -
Program for Implementing STACK using singly linked lists
*/

List *stack_push(List *stack, int32_t item)
{
    if (stack == NULL)
        return NULL;
    return slist_add_head(stack, item);
}

int stack_pop(List *stack, int32_t *item)
{
    if (stack == NULL || stack->head == NULL || item == NULL)
        return 0;

    *item = stack->head->data;
    slist_delete_head(stack);
    return 1;
}

int stack_peek(List *stack, int32_t *item)
{
    if (stack == NULL || stack->head == NULL || item == NULL)
        return 0;

    *item = stack->head->data;
    return 1;
}