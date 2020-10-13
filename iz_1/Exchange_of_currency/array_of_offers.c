#include "array_of_offers.h"

error create_array_of_offers(array_of_offers *arr) {
    offer *buf_offer = (offer*) malloc(DEFAULT_ALLOCATED_SIZE * sizeof(offer));
    if (!buf_offer)
        return MEMORY_ERROR;

    arr->data = buf_offer;
    arr->size = 0;
    arr->allocated_size = DEFAULT_ALLOCATED_SIZE;

    return SUCCESS;
}


error delete_array_of_offers(array_of_offers *arr) {
    if ((!arr) || (!arr->data) || (!arr->allocated_size))
        return NO_DATA;

    free(arr->data);
    arr->data = NULL;
    arr->allocated_size = 0;
    arr->size = 0;

    return SUCCESS;
}

error output_array_of_offers(array_of_offers *arr) {
    if ((!arr) || (!arr->data) || (!arr->allocated_size))
        return NO_DATA;

    error err = SUCCESS;
    printf("\n[");
    for (size_t i = 0; ((i < arr->size) && (!err)); i++) {
        err = output_offer(&arr->data[i]);
        if (i + 1 < arr->size)
            printf(",");
    }
    printf("\n]");

    return err;
}


error resize_array_of_offers(array_of_offers *arr, size_t new_size) {
    if ((!arr) || (!arr->data) || (!arr->allocated_size))
        return NO_DATA;

    if (new_size < arr->allocated_size)
        return BAD_SIZE;

    size_t allocated = arr->allocated_size + (new_size >> 3) + (new_size < 9 ? 3 : 6);

    offer *buf_offer = arr->data;
    buf_offer = (offer*) realloc(buf_offer, allocated * sizeof(offer));
    if (!buf_offer)
        return MEMORY_ERROR;

    arr->data = buf_offer;
    arr->allocated_size = allocated;

    return SUCCESS;
}

error append_into_array_of_offers(array_of_offers *arr, offer *offer) {
    if ((!arr) || (!arr->data) || (!arr->allocated_size) || (!offer))
        return NO_DATA;

    if (arr->size > arr->allocated_size)
        return MEMORY_ERROR;

    error err = SUCCESS;
    if (arr->size == arr->allocated_size)
        err = resize_array_of_offers(arr, arr->size + 1);

    if (!err) {
        arr->data[arr->size] = *offer;
        (arr->size)++;
    }

    return err;
}
