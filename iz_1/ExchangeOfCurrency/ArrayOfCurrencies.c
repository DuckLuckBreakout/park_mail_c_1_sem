#include "ArrayOfCurrencies.h"

Error createArrayOfCurrencies(ArrayOfCurrencies *arr) {
    Error err = SUCCESS;

    Currency *tmp = (Currency*) malloc(DEFAULT_ALLOCATED_SIZE * sizeof(Currency));
    if (tmp) {
        arr->data = tmp;
        arr->size = 0;
        arr->allocated_size = DEFAULT_ALLOCATED_SIZE;
    }
    else
        err = MEMORY_ERROR;
    return err;
}

Error deleteArrayOfCurrencies(ArrayOfCurrencies *arr) {
    if ((!arr) || (!arr->data) || (!arr->allocated_size))
        return NO_DATA;


    free(arr->data);
    arr->data = NULL;
    arr->size = 0;
    arr->allocated_size = 0;

    return SUCCESS;
}

Error resizeArrayOfCurrencies(ArrayOfCurrencies *arr, size_t new_size) {
    if ((!arr) || (!arr->data) || (!arr->allocated_size))
        return NO_DATA;

    if (new_size < arr->allocated_size)
        return BAD_SIZE;

    Error err = SUCCESS;
    Currency *tmp = arr->data;
    size_t allocated = arr->allocated_size + (new_size >> 3) + (new_size < 9 ? 3 : 6);
    tmp = (Currency*) realloc(tmp, allocated * sizeof(Currency));

    if (tmp) {
        arr->data = tmp;
        arr->allocated_size = allocated;
    }
    else
        err = MEMORY_ERROR;

    return err;
}

Error appendIntoArrayOfCurrencies(ArrayOfCurrencies *arr, const Currency *currency) {
    Error err = SUCCESS;

    if (arr->size == arr->allocated_size)
        err = resizeArrayOfCurrencies(arr, arr->size + 1);

    if (!err) {
        strcpy(arr->data[arr->size], *currency);
        (arr->size)++;
    }
    return err;
}

size_t find_currency_index(const ArrayOfCurrencies *arr, const Currency *currency) {
    size_t index = arr->size + 1;
    for (size_t i = 0; (i < arr->size) && (index == arr->size + 1); i++)
        if (!strcmp(*currency, arr->data[i]))
            index = i;

    return index;
}
