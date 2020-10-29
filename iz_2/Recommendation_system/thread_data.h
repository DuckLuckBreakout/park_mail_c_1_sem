#ifndef IZ_2_THREAD_DATA_H
#define IZ_2_THREAD_DATA_H

#include <pthread.h>
#include "user_mark.h"
#include "object.h"
#include "data_struct.h"
#include "objects_rating.h"

typedef struct thread_data {
    int user_id;
    int object_id;
    float obj_rating;
    int sum;
    int size;
    FILE *file;
    data_t *data;
    objects_rating_t *user_rating;
    pthread_mutex_t *mutex;
    user_mark_t mark;
    object_t obj;
} thread_data_t;

#endif //IZ_2_THREAD_DATA_H
