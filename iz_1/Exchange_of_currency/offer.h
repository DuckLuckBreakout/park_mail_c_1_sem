#ifndef IZ_1_OFFER_H
#define IZ_1_OFFER_H

#include "currency_pair.h"

typedef struct offer {
    char bank[MAX_BANK_NAME_LEN];
    currency_pair currency_pair;
    double exchange_rate;
    double bank_fee;
} offer;


error input_offer(offer *elem);
error output_offer(const offer *offer);
error get_result_exchange_rate(const offer* offer, double *result_exchange_rate);
#endif //IZ_1_OFFER_H
