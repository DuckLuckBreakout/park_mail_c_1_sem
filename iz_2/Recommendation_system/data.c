#include "data.h"

error fill_index_array(data_t *data) {
    if ((!data) || (!data->index_array.buffer))
        return NO_DATA;

    error err = SUCCESS;

    FILE *f = fopen(data->file_name, "rb");
    if (!f)
        return INCORRECT_DATA;

    fseek(f, 0, SEEK_SET);
    int seek = 0;
    object_t obj;
    while ((!err) && (fread(&obj, sizeof(object_t), 1, f) == 1)) {
        seek += sizeof(object_t);
        err = append_into_int_array(&data->index_array, seek);
        fseek(f, sizeof(user_mark_t) * obj.marks_count, SEEK_CUR);
        seek += sizeof(user_mark_t) * obj.marks_count;
    }
    fclose(f);
    return err;
}

error init_data(data_t *data, const char file_name[FILENAME_MAX]) {
    if ((!data) || (!file_name[0]))
        return NO_DATA;

    strcpy(data->file_name, file_name);
    error err = create_int_array(&data->index_array);
    fill_index_array(data);
    return err;
}

error delete_data(data_t *data) {
    if (!data)
        return NO_DATA;
    return delete_int_array(&data->index_array);
}

