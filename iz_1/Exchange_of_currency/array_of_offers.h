#ifndef IZ_1_ARRAY_OF_OFFERS_H
#define IZ_1_ARRAY_OF_OFFERS_H

#include <stdlib.h>
#include "offer.h"
#include "constants.h"


typedef struct ArrayOfOffers {
    Offer *data;
    size_t size;
    size_t allocated_size;
} ArrayOfOffers;

Error createArrayOfOffers(ArrayOfOffers *arr);
Error deleteArrayOfOffers(ArrayOfOffers *arr);
Error outputArrayOfOffers(ArrayOfOffers *arr);
Error resizeArrayOfOffers(ArrayOfOffers *arr, size_t new_size);
Error appendIntoArrayOfOffers(ArrayOfOffers *arr, Offer *offer);
#endif //IZ_1_ARRAY_OF_OFFERS_H
