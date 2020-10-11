#ifndef IZ_1_CURRENCYPAIR_H
#define IZ_1_CURRENCYPAIR_H

#include <stdio.h>
#include <string.h>
#include "Currency.h"
#include "../Errors/error_codes.h"
#include "constants.h"

typedef struct CurrencyPair {
    Currency currency_1;
    Currency currency_2;
} CurrencyPair;

Error inputCurrencyPair(CurrencyPair *currency_pair);
Error outputCurrencyPair(const CurrencyPair *currency_pair);
int isEqualCurrencyPair(const CurrencyPair *a, const CurrencyPair *b);

#endif //IZ_1_CURRENCYPAIR_H
