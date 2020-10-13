#include "task_manager.h"

error_t task_manager() {
    printf("\nВведите число предложений: ");
    int number_of_offers;
    if ((scanf("%d", &number_of_offers) != 1) || (number_of_offers <= 0))
        return INPUT_ERROR;

    currency_pair_t target_pair;
    error_t err = input_currency_pair(&target_pair);
    if (err)
        return err;

    currency_exchange_rates_t data;
    create_currency_exchange_rates(&data);
    err = input_currency_exchange_rates(&data, number_of_offers);
    if (err)
        return err;

    array_of_offers_t strategy;
    err = create_array_of_offers(&strategy);
    if (err) {
        delete_currency_exchange_rates(&data);
        return err;
    }

    double best_exchange_rate;
    err = find_best_exchange_rate(&data, &target_pair, &strategy, &best_exchange_rate);

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
        delete_currency_exchange_rates(&data);
    }
    else {
        err = delete_array_of_offers(&strategy);
        if (!err)
            err = delete_currency_exchange_rates(&data);
        else
            delete_currency_exchange_rates(&data);
    }

    return err;
}
