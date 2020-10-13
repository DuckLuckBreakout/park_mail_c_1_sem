#include "currency_pair.h"

error input_currency_pair(currency_pair_t *currency_pair) {
    if (!currency_pair)
        return NO_DATA;

    currency_t buf_carrency;
    printf("\ncurrency_pair: ");

    printf("\nfirst currency: ");
    if (scanf("%s", buf_carrency) != 1)
        return INPUT_ERROR;
    strcpy(currency_pair->currency_1, buf_carrency);

    printf("\nsecond currency: ");
    if (scanf("%s", buf_carrency) != 1)
        return INPUT_ERROR;
    strcpy(currency_pair->currency_2, buf_carrency);

    return SUCCESS;
}

error output_currency_pair(const currency_pair_t *currency_pair) {
    if (!currency_pair)
        return NO_DATA;
    printf("%s/%s", currency_pair->currency_1, currency_pair->currency_2);
    return SUCCESS;
}

int is_equal_currency_pairs(const currency_pair_t *a, const currency_pair_t *b) {
    if ((!a) || (!b))
        return FALSE;
    return ((!strcmp(a->currency_1, b->currency_1)) &&
            (!strcmp(a->currency_2, b->currency_2)));
}
