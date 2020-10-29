#ifndef IZ_2_PARALLEL_H
#define IZ_2_PARALLEL_H

#include <string.h>
#include <unistd.h>
#include "thread_data.h"
#include "user_mark.h"
#include "object.h"
#include "objects_rating.h"

#define THREADS_MAX_COUNT 100


typedef struct threads {
    thread_data_t data[THREADS_MAX_COUNT];
    pthread_t threads[THREADS_MAX_COUNT];
} threads_t;

void *get_object_rating_by_id_parallel(void *thread_data_);
error get_recommendation_for_user_parallel(data_t *data, int user_id, objects_rating_t *user_rating);
error init_threads_data(threads_t *threads, data_t *data, int start_obj_id, int threads_count,
                        int user_id, pthread_mutex_t *mutex, objects_rating_t *user_rating);
error run_threads(threads_t *threads, int threads_count);
error wait_threads(threads_t *threads, int threads_count);
#endif //IZ_2_PARALLEL_H
