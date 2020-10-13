#ifndef IZ_1_ARRAY_OF_OFFERS_H
#define IZ_1_ARRAY_OF_OFFERS_H

#include <stdlib.h>
#include "offer.h"
#include "constants.h"


typedef struct array_of_offers {
    offer *data;
    size_t size;
    size_t allocated_size;
} array_of_offers;

error create_array_of_offers(array_of_offers *arr);
error delete_array_of_offers(array_of_offers *arr);
error output_array_of_offers(array_of_offers *arr);
error resize_array_of_offers(array_of_offers *arr, size_t new_size);
error append_into_array_of_offers(array_of_offers *arr, offer *offer);
#endif //IZ_1_ARRAY_OF_OFFERS_H
