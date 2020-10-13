#include "array_of_offers.h"

Error createArrayOfOffers(ArrayOfOffers *arr) {
    Error err = SUCCESS;

    Offer *tmp = (Offer*) malloc(DEFAULT_ALLOCATED_SIZE * sizeof(Offer));
    if (tmp){
        arr->data = tmp;
        arr->size = 0;
        arr->allocated_size = DEFAULT_ALLOCATED_SIZE;
    }
    else
        err = MEMORY_ERROR;

    return err;
}


Error deleteArrayOfOffers(ArrayOfOffers *arr) {
    if ((!arr) || (!arr->data) || (!arr->allocated_size))
        return NO_DATA;

    free(arr->data);
    arr->data = NULL;
    arr->allocated_size = 0;
    arr->size = 0;

    return SUCCESS;
}

Error outputArrayOfOffers(ArrayOfOffers *arr) {
    if ((!arr) || (!arr->data) || (!arr->allocated_size))
        return NO_DATA;

    Error err = SUCCESS;
    printf("\n[");
    for (size_t i = 0; ((i < arr->size) && (!err)); i++) {
        err = outputOffer(&arr->data[i]);
        if (i + 1 < arr->size)
            printf(",");
    }
    printf("\n]");

    return err;
}


Error resizeArrayOfOffers(ArrayOfOffers *arr, size_t new_size) {
    if ((!arr) || (!arr->data) || (!arr->allocated_size))
        return NO_DATA;

    if (new_size < arr->allocated_size)
        return BAD_SIZE;

    size_t allocated = arr->allocated_size + (new_size >> 3) + (new_size < 9 ? 3 : 6);

    Offer *tmp = arr->data;
    tmp = (Offer*) realloc(tmp, allocated * sizeof(Offer));
    if (tmp) {
        arr->data = tmp;
        arr->allocated_size = allocated;
    }
    else
        return MEMORY_ERROR;

    return SUCCESS;
}

Error appendIntoArrayOfOffers(ArrayOfOffers *arr, Offer *offer) {
    if ((!arr) || (!arr->data) || (!arr->allocated_size) || (!offer))
        return NO_DATA;

    if (arr->size > arr->allocated_size)
        return MEMORY_ERROR;

    Error err = SUCCESS;
    if (arr->size == arr->allocated_size)
        err = resizeArrayOfOffers(arr, arr->size + 1);

    if (!err) {
        arr->data[arr->size] = *offer;
        (arr->size)++;
    }

    return err;
}
