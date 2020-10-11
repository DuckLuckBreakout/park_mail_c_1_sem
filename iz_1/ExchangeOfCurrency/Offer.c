#include "Offer.h"

Error inputOffer(Offer *elem){
    Error err = SUCCESS;
    Offer tmp_offer;

    puts("bank: ");
    if (scanf("%s", tmp_offer.bank) != 1)
        return INPUT_ERROR;

    err = inputCurrencyPair(&tmp_offer.currency_pair);
    if (err)
        return err;

    puts("exchange_rate: ");
    if ((scanf("%lf", &tmp_offer.exchange_rate) != 1) || (tmp_offer.exchange_rate <= 0))
        return INPUT_ERROR;

    puts("bank_fee: ");
    if ((scanf("%lf", &tmp_offer.bank_fee) != 1) || (tmp_offer.bank_fee < 0))
        return INPUT_ERROR;

    strcpy(elem->bank, tmp_offer.bank);
    elem->bank_fee = tmp_offer.bank_fee;
    elem->exchange_rate = tmp_offer.exchange_rate;
    elem->currency_pair = tmp_offer.currency_pair;

    return SUCCESS;
}

Error outputOffer(const Offer *elem) {
    if (!elem)
        return NO_DATA;

    printf("\n\t{\n");
    printf("\t\t\"bank\": \"%s\", \n", elem->bank);
    printf("\t\t\"CurrencyPair\": \"");
    Error err = outputCurrencyPair(&elem->currency_pair);
    printf("\",\n");
    printf("\t\t\"exchange_rate\": %lf,\n", elem->exchange_rate);
    printf("\t\t\"bank_fee\": %lf\n", elem->bank_fee);
    printf("\t}");
    return err;
}

Error getResultExchangeRate(const Offer* offer, double *result_exchange_rate) {
    if (!offer)
        return NO_DATA;

    (*result_exchange_rate) = offer->exchange_rate * (1 - offer->bank_fee);
    return SUCCESS;
}
