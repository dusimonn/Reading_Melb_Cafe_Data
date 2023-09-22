#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct declarations
typedef struct node node_t;
struct node {
    node_t *next;
    record_t record;
};

typedef struct {
    node_t *head;
    node_t *tail;
} list_t;

// function prototypes
/* creates an empty linked list to store dataset records */
list_t *make_list(void);
/* inserts a record from dataset into the linked list */
list_t *insert_record(list_t *record_list, record_t *new_record);
/* searches the record list for a matching key = trading name */
int search_list(list_t *record_list, char *key, FILE *outfile);
/* outputs the matching record to the outfile */
void print_to_outfile(FILE *outfile, node_t *current, int num_matches);
/* free the memory associated with the record list */
void free_list(list_t *record_list);

#endif
