#ifndef IZ_1_OFFER_H
#define IZ_1_OFFER_H

#include "currency_pair.h"

typedef struct Offer {
    char bank[10];
    CurrencyPair currency_pair;
    double exchange_rate;
    double bank_fee;
} Offer;


Error inputOffer(Offer *elem);
Error outputOffer(const Offer *elem);
Error getResultExchangeRate(const Offer* offer, double *result_exchange_rate);
#endif //IZ_1_OFFER_H
