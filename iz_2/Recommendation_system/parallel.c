#include "parallel.h"

void *get_object_rating_by_id_parallel(void *thread_data_) {
    thread_data_t *thread_data = (thread_data_t*) thread_data_;

    if (!thread_data)
        pthread_exit(0);

    if ((thread_data->object_id < 0) || (thread_data->user_id < 0))
        pthread_exit(0);

    fseek(thread_data->file, thread_data->data->index_array.buffer[thread_data->object_id] - sizeof(object_t), SEEK_SET);

    fread(&thread_data->obj, sizeof(object_t), 1, thread_data->file);
    for (int i = 0; i < thread_data->obj.marks_count; i++) {
        fread(&thread_data->mark, sizeof(user_mark_t), 1, thread_data->file);
        if (thread_data->mark.user_id == thread_data->user_id)
            pthread_exit(0);
        thread_data->sum += thread_data->mark.mark;
        thread_data->size++;
    }
    fclose(thread_data->file);

    if (thread_data->size)
        (thread_data->obj_rating) = (float)thread_data->sum / (float)thread_data->size;


    pthread_mutex_lock(thread_data->mutex);
    if (thread_data->obj_rating > thread_data->user_rating->ratings[RATING_SIZE - 1])
        update_objects_rating(thread_data->user_rating, thread_data->object_id, thread_data->obj_rating);
    pthread_mutex_unlock(thread_data->mutex);

    pthread_exit(0);

}

error get_recommendation_for_user_parallel(data_t *data, int user_id, objects_rating_t *user_rating) {

    if ((!data) || (!user_rating))
        return NO_DATA;

    if (user_id < 0)
        return INCORRECT_DATA;

    error err = SUCCESS;

    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

    threads_t threads;

    int threads_count = sysconf(_SC_NPROCESSORS_ONLN);
    for (int i = 0; i < data->index_array.size; i += threads_count) {

        if (i + threads_count >= data->index_array.size)
            threads_count = data->index_array.size - i;

        init_threads_data(&threads, data, i, threads_count, user_id, &mutex, user_rating);

        err = run_threads(&threads, threads_count);
        if (!err)
            err = wait_threads(&threads, threads_count);
    }

    pthread_mutex_destroy(&mutex);

    return err;
}

error wait_threads(threads_t *threads, int threads_count) {
    error err = SUCCESS;
    for (size_t j = 0; (j < threads_count); j++)
        err = pthread_join(threads->threads[j], NULL);
    return err;
}

error run_threads(threads_t *threads, int threads_count) {
    error err = SUCCESS;
    for (int i = 0;(!err) && (i < threads_count); i++)
        err = pthread_create(threads->threads + i, NULL, get_object_rating_by_id_parallel, threads->data + i);
    return err;
}

error init_threads_data(threads_t *threads, data_t *data, int start_obj_id, int threads_count,
                        int user_id, pthread_mutex_t *mutex, objects_rating_t *user_rating) {

    if ((!threads) || (!data) || (!mutex) || (!user_rating))
        return NO_DATA;

    if ((start_obj_id < 0) || (threads_count < 0) || (user_id < 0))
        return INCORRECT_DATA;

    for (int i = 0; i < threads_count; i++) {
        thread_data_t thread_data;
        thread_data.obj_rating = 0;
        thread_data.user_id = user_id;
        thread_data.data = data;
        thread_data.object_id = start_obj_id + i;
        thread_data.mutex = mutex;
        thread_data.user_rating = user_rating;
        thread_data.sum = 0;
        thread_data.size = 0;
        thread_data.file = fopen(data->file_name, "rb");
        if (!thread_data.file)
            return NO_DATA;
        object_t obj;
        obj.id = -1;
        obj.marks_count = -1;
        strcpy(obj.name, "name");
        thread_data.obj = obj;
        user_mark_t mark = {-1, -1};
        thread_data.mark = mark;
        threads->data[i] = thread_data;
    }
    return SUCCESS;
}
