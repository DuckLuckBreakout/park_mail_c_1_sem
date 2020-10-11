#include "CurrencyPair.h"

Error inputCurrencyPair(CurrencyPair *currency_pair) {
    char tmp[4];
    printf("\ncurrency_pair: ");

    printf("\nfirst currency: ");
    if (scanf("%s", tmp) != 1)
        return INPUT_ERROR;
    strcpy(currency_pair->currency_1, tmp);

    printf("\nsecond currency: ");
    if (scanf("%s", tmp) != 1)
        return INPUT_ERROR;
    strcpy(currency_pair->currency_2, tmp);

    return SUCCESS;
}

Error outputCurrencyPair(const CurrencyPair *currency_pair) {
    if (!currency_pair)
        return NO_DATA;
    printf("%s/%s", currency_pair->currency_1, currency_pair->currency_2);
    return SUCCESS;
}

int isEqualCurrencyPair(const CurrencyPair *a, const CurrencyPair *b) {
    if ((!a) || (!b))
        return FALSE;
    return (!strcmp(a->currency_1, b->currency_1)) && (!strcmp(a->currency_2, b->currency_2));
}
