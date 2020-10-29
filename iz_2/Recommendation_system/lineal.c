#include "lineal.h"


error get_object_rating_by_id_lineal(data_t *data, int obj_id, int user_id, float *obj_rating) {
    if ((!data) || (!obj_rating))
        return NO_DATA;

    if ((obj_id < 0) || (user_id < 0))
        return INCORRECT_DATA;

    FILE *f = fopen(data->file_name, "rb");
    if (!f)
        return INCORRECT_DATA;

    fseek(f, data->index_array.buffer[obj_id] - sizeof(object_t), SEEK_SET);

    int sum = 0;
    int size = 0;
    user_mark_t mark;
    object_t obj;
    fread(&obj, sizeof(object_t), 1, f);
    for (int i = 0; i < obj.marks_count; i++) {
        fread(&mark, sizeof(mark), 1, f);
        if (mark.user_id == user_id)
            return SUCCESS;
        sum += mark.mark;
        size++;
    }
    fclose(f);

    if (size)
        (*obj_rating) = (float)sum / (float)size;
    return SUCCESS;
}

error get_recommendation_for_user_lineal(data_t *data, int user_id, objects_rating_t *user_rating) {
    if ((!data) || (!user_rating))
        return NO_DATA;

    if (user_id < 0)
        return INCORRECT_DATA;

    error err = SUCCESS;
    for (int obj_id = 0; (!err) && (obj_id < data->index_array.size); obj_id++) {
        float obj_rating = 0;
        err = get_object_rating_by_id_lineal(data, obj_id, user_id, &obj_rating);
        if ((!err) && (obj_rating > user_rating->ratings[RATING_SIZE - 1]))
            err = update_objects_rating(user_rating, obj_id, obj_rating);
    }
    return err;
}
