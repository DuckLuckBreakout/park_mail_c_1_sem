#ifndef IZ_1_OFFER_H
#define IZ_1_OFFER_H

#include "currency_pair.h"

typedef struct offer_t {
    char bank[MAX_BANK_NAME_LEN];
    currency_pair_t currency_pair;
    double exchange_rate;
    double bank_fee;
} offer_t;


error input_offer(offer_t *elem);
error output_offer(const offer_t *offer);
error get_result_exchange_rate(const offer_t* offer, double *result_exchange_rate);
#endif //IZ_1_OFFER_H
