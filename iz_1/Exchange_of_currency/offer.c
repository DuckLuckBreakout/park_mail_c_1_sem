#include "offer.h"

error input_offer(offer *elem){
    offer buf_offer;

    puts("bank: ");
    if (scanf("%s", buf_offer.bank) != 1)
        return INPUT_ERROR;

    error err = input_currency_pair(&buf_offer.currency_pair);
    if (err)
        return err;

    puts("exchange_rate: ");
    if ((scanf("%lf", &buf_offer.exchange_rate) != 1) ||
        (buf_offer.exchange_rate <= 0))
        return INPUT_ERROR;

    puts("bank_fee: ");
    if ((scanf("%lf", &buf_offer.bank_fee) != 1) ||
        (buf_offer.bank_fee < 0))
        return INPUT_ERROR;

    strcpy(elem->bank, buf_offer.bank);
    elem->bank_fee = buf_offer.bank_fee;
    elem->exchange_rate = buf_offer.exchange_rate;
    elem->currency_pair = buf_offer.currency_pair;

    return SUCCESS;
}

error output_offer(const offer *offer) {
    if (!offer)
        return NO_DATA;

    printf("\n\t{\n");
    printf("\t\t\"bank\": \"%s\", \n", offer->bank);
    printf("\t\t\"currency_pair\": \"");
    error err = output_currency_pair(&offer->currency_pair);
    printf("\",\n");
    printf("\t\t\"exchange_rate\": %lf,\n", offer->exchange_rate);
    printf("\t\t\"bank_fee\": %lf\n", offer->bank_fee);
    printf("\t}");
    return err;
}

error get_result_exchange_rate(const offer* offer, double *result_exchange_rate) {
    if (!offer)
        return NO_DATA;

    (*result_exchange_rate) = offer->exchange_rate * (1 - offer->bank_fee);
    return SUCCESS;
}
