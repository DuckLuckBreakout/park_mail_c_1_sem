#include "task_manager.h"

error task_manager(task_flags_t *task_flags) {
    if (!task_flags)
        return NO_DATA;

    error err;

    data_t objects_data;
    err = init_data(&objects_data, task_flags->source);
    if (err)
        return err;

    int user_id;
    if (task_flags->user_id == -1) {
        if ((scanf("%d", &user_id) != 1) || (user_id < 0)) {
            delete_data(&objects_data);
            return INPUT_ERROR;
        }
    }
    else
        user_id = task_flags->user_id;

    objects_rating_t user_rating;
    err = init_objects_rating(&user_rating);
    if (err) {
        delete_data(&objects_data);
        return err;
    }

    if (task_flags->parallel)
        err = get_recommendation_for_user_parallel(&objects_data, user_id, &user_rating);
    else
        err = get_recommendation_for_user_lineal(&objects_data, user_id, &user_rating);

    if (err) {
        delete_data(&objects_data);
        return err;
    }

    if (strcmp(task_flags->target, "STDOUT")) {
        FILE *f = fopen(task_flags->target, "w");
        print_objects_rating(&user_rating, f);
        fclose(f);
    }
    else
        print_objects_rating(&user_rating, stdout);

    err = delete_data(&objects_data);
    return err;
}
