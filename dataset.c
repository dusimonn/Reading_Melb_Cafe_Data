#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dataset.h"

// function definitions
/*scans in a record from input dataset */
record_t *
read_record(FILE *datafile) {

    record_t *record = (record_t *) malloc(sizeof(*record));
    assert(record != NULL);

    /* scan in the first 4 elements */
    fscanf(datafile, "%d,%d,%d,%d,", &record->census_year, &record->block_id,
           &record->property_id, &record->base_property_id);

    /* the 5-8th field are strings so remove " " if necessary */
    remove_quotes(datafile, record->building_address);
    remove_quotes(datafile, record->clue_small_area);
    remove_quotes(datafile, record->business_address);
    remove_quotes(datafile, record->trading_name);

    /* scan in elements 9*/
    fscanf(datafile, "%d,", &record->industry_code);

    /* the 10-11th field are strings so remove " " if necessary */
    remove_quotes(datafile, record->industry_description);
    remove_quotes(datafile, record->seating_type);

    /* scan in the rest of the elements */
    fscanf(datafile, "%d,%lf,%lf\n",
           &record->number_of_seats, &record->longitude, &record->latitude);

    return record;
}

/* process the next csv string field to remove " " if necessary and store*/
void
remove_quotes(FILE *datafile, char *field) {
    if (fscanf(datafile, "%*[\"]%[^\"]%*[\"],", field) == 1) {
    } else {
        fscanf(datafile, "%[^,],", field);
    }
}
