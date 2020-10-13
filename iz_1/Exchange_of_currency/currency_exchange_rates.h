#ifndef IZ_1_CURRENCY_EXCHANGE_RATES_H
#define IZ_1_CURRENCY_EXCHANGE_RATES_H

#include <math.h>
#include "array_of_currencies.h"
#include "array_of_offers.h"

typedef struct currency_exchange_rates_t {
    offer_t **data;
    array_of_currencies_t currencies;
    size_t size;
    size_t allocated_size;
} currency_exchange_rates_t;

error_t create_currency_exchange_rates(currency_exchange_rates_t *data);
error_t delete_currency_exchange_rates(currency_exchange_rates_t *data);
error_t input_currency_exchange_rates(currency_exchange_rates_t *data,
                                      size_t number_of_offers);
error_t resize_currency_exchange_rates(currency_exchange_rates_t *data,
                                       size_t new_size);

error_t find_best_exchange_rate(const currency_exchange_rates_t *data,
                                const currency_pair_t *currencyPair,
                                array_of_offers_t *strategy,
                                double *best_exchange_rate);
#endif //IZ_1_CURRENCY_EXCHANGE_RATES_H
