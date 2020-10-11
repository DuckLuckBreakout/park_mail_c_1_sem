#ifndef IZ_1_CURRENCYEXCHANGERATES_H
#define IZ_1_CURRENCYEXCHANGERATES_H

#include <math.h>
#include "ArrayOfCurrencies.h"
#include "ArrayOfOffers.h"

typedef struct CurrencyExchangeRates {
    Offer **data;
    ArrayOfCurrencies currencies;
    size_t size;
    size_t allocated_size;
} CurrencyExchangeRates;

Error createCurrencyExchangeRates(CurrencyExchangeRates *data);
Error deleteCurrencyExchangeRates(CurrencyExchangeRates *data);
Error inputCurrencyExchangeRates(CurrencyExchangeRates *data, size_t number_of_offers);

Error find_best_exchange_rate(const CurrencyExchangeRates *data, const CurrencyPair *currencyPair,
                              ArrayOfOffers *strategy, double *best_exchange_rate);
#endif //IZ_1_CURRENCYEXCHANGERATES_H
