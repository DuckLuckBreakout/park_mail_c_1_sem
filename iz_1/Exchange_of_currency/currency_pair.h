#ifndef IZ_1_CURRENCY_PAIR_H
#define IZ_1_CURRENCY_PAIR_H

#include <stdio.h>
#include <string.h>
#include "currency.h"
#include "Errors/error_codes.h"
#include "constants.h"

typedef struct currency_pair {
    currency currency_1;
    currency currency_2;
} currency_pair;

error input_currency_pair(currency_pair *currency_pair);
error output_currency_pair(const currency_pair *currency_pair);
int is_equal_currency_pairs(const currency_pair *a, const currency_pair *b);

#endif //IZ_1_CURRENCY_PAIR_H
