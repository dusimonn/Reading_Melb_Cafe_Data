#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dataset.h"
#include "linkedlist.h"

// function definitions
/* creates an empty linked list to store dataset records */
list_t *
make_list(void) {
    list_t *record_list;
    record_list = (list_t *) malloc(sizeof(*record_list));
    assert(record_list != NULL);
    record_list->head = NULL;
    record_list->tail = NULL;
    return record_list;
}

/* inserts a record from dataset into the linked list */
list_t *
insert_record(list_t *record_list, record_t *new_record) {
    assert(record_list != NULL);
    node_t *new = (node_t *) malloc(sizeof(*new));
    assert(new != NULL);
    new->record = *new_record;
    new->next = NULL;

    if (record_list->head == NULL) {
        /* this is the only item in the list */
        record_list->tail = new;
        record_list->head = new;
    } else {
        /* insert record at the tail of list */
        record_list->tail->next = new;
        record_list->tail = new;
    }

    return record_list;
}

/* searches the record list for a matching key = trading name */
int
search_list(list_t *record_list, char *key, FILE *outfile) {

    assert(record_list != NULL);
    node_t *current = record_list->head;
    int num_matches = 0;

    /* travel along list to find a match */
    while (current) {
        if (strcmp(current->record.trading_name, key) == 0) {
            num_matches++;
            /* output the match */
            print_to_outfile(outfile, current, num_matches);
        }
        current = current->next;
    }

    return num_matches;
}

/* outputs the matching record to the outfile */
void
print_to_outfile(FILE *outfile, node_t *current, int num_matches) {

    /* this is the first match */
    if (num_matches == 1) {
        fprintf(outfile, "%s\n", current->record.trading_name);
    }

    /* split up the fprintf statement into multiple because too messy if all in 1 */
    fprintf(outfile,
            "--> census_year: %d || block_id: %d || property_id: %d "
            "|| base_property_id: %d || ",
            current->record.census_year, current->record.block_id,
            current->record.property_id, current->record.base_property_id);

    fprintf(outfile,
            "building_address: %s || clue_small_area: %s || "
            "business_address: %s || trading_name: %s || ",
            current->record.building_address, current->record.clue_small_area,
            current->record.business_address, current->record.trading_name);

    fprintf(outfile,
            "industry_code: %d || industry_description: %s || "
            "seating_type: %s || number_of_seats: %d || ",
            current->record.industry_code, current->record.industry_description,
            current->record.seating_type, current->record.number_of_seats);

    fprintf(outfile, "longitude: %.5lf || latitude: %.5lf || \n",
            current->record.longitude, current->record.latitude);
}

/* free the memory associated with the record list */
void
free_list(list_t *record_list) {
    assert(record_list != NULL);
    node_t *current = record_list->head;

    while (current) {
        node_t *prev = current;
        current = current->next;
        free(prev);
    }

    free(record_list);
}
