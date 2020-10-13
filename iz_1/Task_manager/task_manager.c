#include "task_manager.h"

Error task_manager() {
    printf("\nВведите число предложений: ");
    int number_of_offers;
    if ((scanf("%d", &number_of_offers) != 1) || (number_of_offers <= 0))
        return INPUT_ERROR;

    CurrencyPair target_pair;
    Error err = inputCurrencyPair(&target_pair);
    if (err)
        return err;

    CurrencyExchangeRates currencyExchangeRates;
    createCurrencyExchangeRates(&currencyExchangeRates);
    err = inputCurrencyExchangeRates(&currencyExchangeRates, number_of_offers);
    if (err)
        return err;

    ArrayOfOffers strategy;
    err = createArrayOfOffers(&strategy);
    if (err) {
        deleteCurrencyExchangeRates(&currencyExchangeRates);
        return err;
    }

    double best_exchange_rate;
    err = find_best_exchange_rate(&currencyExchangeRates, &target_pair, &strategy, &best_exchange_rate);

    if (!err){
        printf("\nBest exchange rate for ");
        err = outputCurrencyPair(&target_pair);
        if (!err) {
            printf("= %lf ", best_exchange_rate);
            err = outputArrayOfOffers(&strategy);
        }
    }

    if (err) {
        deleteArrayOfOffers(&strategy);
        deleteCurrencyExchangeRates(&currencyExchangeRates);
    }
    else {
        err = deleteArrayOfOffers(&strategy);
        if (!err)
            err = deleteCurrencyExchangeRates(&currencyExchangeRates);
        else
            deleteCurrencyExchangeRates(&currencyExchangeRates);
    }

    return err;
}
