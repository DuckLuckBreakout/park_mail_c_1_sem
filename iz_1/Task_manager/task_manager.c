#include "task_manager.h"

error task_manager() {
    printf("\nВведите число предложений: ");
    int number_of_offers;
    if ((scanf("%d", &number_of_offers) != 1) || (number_of_offers <= 0))
        return INPUT_ERROR;

    currency_pair target_pair;
    error err = input_currency_pair(&target_pair);
    if (err)
        return err;

    currency_exchange_rates currencyExchangeRates;
    create_currency_exchange_rates(&currencyExchangeRates);
    err = input_currency_exchange_rates(&currencyExchangeRates, number_of_offers);
    if (err)
        return err;

    array_of_offers strategy;
    err = create_array_of_offers(&strategy);
    if (err) {
        delete_currency_exchange_rates(&currencyExchangeRates);
        return err;
    }

    double best_exchange_rate;
    err = find_best_exchange_rate(&currencyExchangeRates, &target_pair, &strategy, &best_exchange_rate);

    if (!err){
        printf("\nBest exchange rate for ");
        err = output_currency_pair(&target_pair);
        if (!err) {
            printf("= %lf ", best_exchange_rate);
            err = output_array_of_offers(&strategy);
        }
    }

    if (err) {
        delete_array_of_offers(&strategy);
        delete_currency_exchange_rates(&currencyExchangeRates);
    }
    else {
        err = delete_array_of_offers(&strategy);
        if (!err)
            err = delete_currency_exchange_rates(&currencyExchangeRates);
        else
            delete_currency_exchange_rates(&currencyExchangeRates);
    }

    return err;
}
