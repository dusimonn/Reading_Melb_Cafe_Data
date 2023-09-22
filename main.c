#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dataset.h"
#include "linkedlist.h"

#define STAGE_1  1
#define NOTFOUND 0

int
main(int argc, char **argv) {

    /* initialise input and output files */
    FILE *data_file = fopen(argv[2], "r");
    assert(data_file != NULL);
    FILE *out_file = fopen(argv[3], "w");
    assert(out_file != NULL);

    /* create linked list to store records */
    list_t *record_list = make_list();

    /* read and disregard the header */
    char header[MAX_DATASET];
    fscanf(data_file, "%[^\n]\n", header);

    /* processing dataset */
    while (!feof(data_file)) {
        /* read each record */
        record_t *record = read_record(data_file);
        /* insert the record into the linked list */
        insert_record(record_list, record);

        free(record);
    }

    /* processing trading_names from stdin */
    while (!feof(stdin)) {
        char trading_name[MAX_FIELD];
        fscanf(stdin, "%[^\n]\n", trading_name);

        /* find any matching records in list and output match to outfile */
        int matches = search_list(record_list, trading_name, out_file);

        /* output number of matches to stdout */
        fprintf(stdout, "%s --> %d\n", trading_name, matches);
    }

    /* clean up */
    free_list(record_list);
    fclose(data_file);
    fclose(out_file);
    return 0;
}
