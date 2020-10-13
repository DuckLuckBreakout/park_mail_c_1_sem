#ifndef IZ_1_CURRENCY_EXCHANGE_RATES_H
#define IZ_1_CURRENCY_EXCHANGE_RATES_H

#include <math.h>
#include "array_of_currencies.h"
#include "array_of_offers.h"

typedef struct currency_exchange_rates {
    offer **data;
    array_of_currencies currencies;
    size_t size;
    size_t allocated_size;
} currency_exchange_rates;

error create_currency_exchange_rates(currency_exchange_rates *data);
error delete_currency_exchange_rates(currency_exchange_rates *data);
error input_currency_exchange_rates(currency_exchange_rates *data,
                                    size_t number_of_offers);
error resize_currency_exchange_rates(currency_exchange_rates *data,
                                     size_t new_size);

error find_best_exchange_rate(const currency_exchange_rates *data,
                              const currency_pair *currencyPair,
                              array_of_offers *strategy,
                              double *best_exchange_rate);
#endif //IZ_1_CURRENCY_EXCHANGE_RATES_H
