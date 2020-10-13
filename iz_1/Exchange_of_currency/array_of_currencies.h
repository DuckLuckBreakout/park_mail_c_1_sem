#ifndef IZ_1_ARRAY_OF_CURRENCIES_H
#define IZ_1_ARRAY_OF_CURRENCIES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "currency.h"
#include "constants.h"
#include "Errors/error_codes.h"


typedef struct array_of_currencies_t {
    currency_t *data;
    size_t size;
    size_t allocated_size;
} array_of_currencies_t;

error create_array_of_currencies(array_of_currencies_t *arr);
error delete_array_of_currencies(array_of_currencies_t *arr);
error resize_array_of_currencies(array_of_currencies_t *arr, size_t new_size);
error append_into_array_of_currencies(array_of_currencies_t *arr,
                                      const currency_t *currency);

size_t find_currency_index(const array_of_currencies_t *arr,
                           const currency_t *currency);

#endif //IZ_1_ARRAY_OF_CURRENCIES_H
