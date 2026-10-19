// Header File
// studentslist.h

/*
Theory Assignment - Ques-4
Program to store student data in a Singly Linked List
*/
#ifndef __INCLUDED_STUDENTLIST__
#define __INCLUDED_STUDENTLIST__
#include <stdio.h>
#include <stdint.h>

typedef struct _student_node_ StNode;
typedef struct _student_list_ StList;

struct _student_node_
{
    uint32_t roll_no;
    char name[50];
    float marks1;
    float marks2;
    StNode *next;
};

struct _student_list_
{
    StNode *head;
    StNode *tail;
    uint32_t length;
};

StList *stlist_new();
StList *stlist_free(StList *);

// uint32_t stlist_length(const StList *list);
// uint32_t stlist_lookup(const StList *list, int32_t data);
// StList *stlist_add_head(StList *list, int32_t data);
// StList *stlist_delete_head(StList *list);

StList *stlist_add_tail(StList *, uint32_t, const char *, float, float);
StList *stlist_delete_on_roll_no(StList *, uint32_t);
// StList *stlist_delete_tail(StList *list);

#endif
