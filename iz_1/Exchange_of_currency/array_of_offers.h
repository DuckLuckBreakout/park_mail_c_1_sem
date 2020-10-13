#ifndef IZ_1_ARRAY_OF_OFFERS_H
#define IZ_1_ARRAY_OF_OFFERS_H

#include <stdlib.h>
#include "offer.h"
#include "constants.h"


typedef struct array_of_offers_t {
    offer_t *data;
    size_t size;
    size_t allocated_size;
} array_of_offers_t;

error_t create_array_of_offers(array_of_offers_t *arr);
error_t delete_array_of_offers(array_of_offers_t *arr);
error_t output_array_of_offers(array_of_offers_t *arr);
error_t resize_array_of_offers(array_of_offers_t *arr, size_t new_size);
error_t append_into_array_of_offers(array_of_offers_t *arr, offer_t *offer);
#endif //IZ_1_ARRAY_OF_OFFERS_H
