#ifndef IZ_1_ARRAY_OF_CURRENCIES_H
#define IZ_1_ARRAY_OF_CURRENCIES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "currency.h"
#include "constants.h"
#include "Errors/error_codes.h"


typedef struct ArrayOfCurrencies {
    Currency *data;
    size_t size;
    size_t allocated_size;
} ArrayOfCurrencies;

Error createArrayOfCurrencies(ArrayOfCurrencies *arr);
Error deleteArrayOfCurrencies(ArrayOfCurrencies *arr);
Error resizeArrayOfCurrencies(ArrayOfCurrencies *arr, size_t new_size);
Error appendIntoArrayOfCurrencies(ArrayOfCurrencies *arr, const Currency *currency);

size_t find_currency_index(const ArrayOfCurrencies *arr, const Currency *currency);

#endif //IZ_1_ARRAY_OF_CURRENCIES_H
