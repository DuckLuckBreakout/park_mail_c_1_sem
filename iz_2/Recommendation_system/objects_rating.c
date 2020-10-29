#include "objects_rating.h"

error init_objects_rating(objects_rating_t *rating) {
    if (!rating)
        return NO_DATA;

    for (int i = 0; i < RATING_SIZE; i++) {
        rating->ratings[i] = 0;
        rating->ids[i] = -1;
    }
    return SUCCESS;
}

error update_objects_rating(objects_rating_t *rating, int obj_id, float obj_rating) {
    if (!rating)
        return NO_DATA;

    if ((obj_id < 0) || (obj_rating < 0) || (obj_rating > 5))
        return INCORRECT_DATA;

    int i;
    for (i = 0; (i < RATING_SIZE) && (rating->ratings[i] > obj_rating); i++) {}
    for (int j = RATING_SIZE - 1; j > i; j--) {
        rating->ratings[j] = rating->ratings[j - 1];
        rating->ids[j] = rating->ids[j - 1];
    }
    rating->ratings[i] = obj_rating;
    rating->ids[i] = obj_id;
    return SUCCESS;
}

error print_objects_rating(objects_rating_t *rating, FILE *f) {
    if (!rating)
        return NO_DATA;

    for (int i = 0; i < RATING_SIZE; i++)
        fprintf(f, "\n%d) object_id: %d", i + 1, rating->ids[i]);

    return SUCCESS;
}