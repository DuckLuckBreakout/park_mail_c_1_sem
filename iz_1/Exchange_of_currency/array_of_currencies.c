#include "array_of_currencies.h"

error create_array_of_currencies(array_of_currencies *arr) {
    currency *buf_currency = (currency*) malloc(DEFAULT_ALLOCATED_SIZE * sizeof(currency));
    if (!buf_currency)
        return MEMORY_ERROR;

    arr->data = buf_currency;
    arr->size = 0;
    arr->allocated_size = DEFAULT_ALLOCATED_SIZE;

    return SUCCESS;
}

error delete_array_of_currencies(array_of_currencies *arr) {
    if ((!arr) || (!arr->data) || (!arr->allocated_size))
        return NO_DATA;

    free(arr->data);
    arr->data = NULL;
    arr->size = 0;
    arr->allocated_size = 0;

    return SUCCESS;
}

error resize_array_of_currencies(array_of_currencies *arr, size_t new_size) {
    if ((!arr) || (!arr->data) || (!arr->allocated_size))
        return NO_DATA;

    if (new_size < arr->allocated_size)
        return BAD_SIZE;

    currency *buf_currency = arr->data;
    size_t allocated = arr->allocated_size + (new_size >> 3) + (new_size < 9 ? 3 : 6);
    buf_currency = (currency*) realloc(buf_currency, allocated * sizeof(currency));
    if (!buf_currency)
        return MEMORY_ERROR;

    arr->data = buf_currency;
    arr->allocated_size = allocated;

    return SUCCESS;
}

error append_into_array_of_currencies(array_of_currencies *arr,
                                      const currency *currency) {
    error err = SUCCESS;

    if (arr->size == arr->allocated_size)
        err = resize_array_of_currencies(arr, arr->size + 1);

    if (!err) {
        strcpy(arr->data[arr->size], *currency);
        (arr->size)++;
    }
    return err;
}

size_t find_currency_index(const array_of_currencies *arr,
                           const currency *currency) {
    size_t index = arr->size + 1;
    for (size_t i = 0; (i < arr->size) && (index == arr->size + 1); i++)
        if (!strcmp(*currency, arr->data[i]))
            index = i;

    return index;
}
