#include "int_array.h"

error create_int_array(int_array_t *arr) {
    int *buf_int = (int*) malloc(DEFAULT_ALLOCATED_SIZE * sizeof(int));
    if (!buf_int)
        return MEMORY_ERROR;

    arr->buffer = buf_int;
    arr->size = 0;
    arr->allocated_size = DEFAULT_ALLOCATED_SIZE;

    return SUCCESS;
}


error delete_int_array(int_array_t *arr) {
    if ((!arr) || (!arr->buffer) || (!arr->allocated_size))
        return NO_DATA;

    free(arr->buffer);
    arr->buffer = NULL;
    arr->allocated_size = 0;
    arr->size = 0;

    return SUCCESS;
}

error resize_int_array(int_array_t *arr, int new_size) {
    if ((!arr) || (!arr->buffer) || (!arr->allocated_size))
        return NO_DATA;

    if (new_size < arr->allocated_size)
        return BAD_SIZE;

    int allocated = arr->allocated_size + (new_size >> 3) + (new_size < 9 ? 3 : 6);

    int *buf_int = arr->buffer;
    buf_int = (int*) realloc(buf_int, allocated * sizeof(int));
    if (!buf_int)
        return MEMORY_ERROR;

    arr->buffer = buf_int;
    arr->allocated_size = allocated;
    buf_int = NULL;
    return SUCCESS;
}

error append_into_int_array(int_array_t *arr, int val) {
    if ((!arr) || (!arr->buffer) || (!arr->allocated_size))
        return NO_DATA;

    if (arr->size > arr->allocated_size)
        return MEMORY_ERROR;

    error err = SUCCESS;
    if (arr->size == arr->allocated_size)
        err = resize_int_array(arr, arr->size + 1);

    if (!err) {
        arr->buffer[arr->size] = val;
        (arr->size)++;
    }

    return err;
}
