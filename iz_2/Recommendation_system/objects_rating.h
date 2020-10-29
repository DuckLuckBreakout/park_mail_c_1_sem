#ifndef IZ_2_OBJECTS_RATING_H
#define IZ_2_OBJECTS_RATING_H

#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "Errors/error_codes.h"

typedef struct objects_rating {
    int ids[RATING_SIZE];
    float ratings[RATING_SIZE];
} objects_rating_t;

error init_objects_rating(objects_rating_t *rating);
error update_objects_rating(objects_rating_t *rating, int obj_id, float obj_rating);
error print_objects_rating(objects_rating_t *rating, FILE *f);

#endif //IZ_2_OBJECTS_RATING_H
