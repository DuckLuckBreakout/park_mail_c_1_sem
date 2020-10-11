#include "CurrencyExchangeRates.h"

#define SIZE 100

Error createCurrencyExchangeRates(CurrencyExchangeRates *data) {
    CurrencyExchangeRates tmp;
    Error err = createArrayOfCurrencies(&tmp.currencies);
    if (err)
        return MEMORY_ERROR;

    tmp.data = (Offer**) malloc(DEFAULT_ALLOCATED_SIZE * sizeof(Offer*));
    if (!tmp.data) {
        deleteArrayOfCurrencies(&tmp.currencies);
        return MEMORY_ERROR;
    }

    for (size_t i = 0; (i < DEFAULT_ALLOCATED_SIZE); i++) {
        tmp.data[i] = (Offer*) malloc(DEFAULT_ALLOCATED_SIZE * sizeof(Offer));
        if (!tmp.data[i]) {
            for (size_t j = 0; j < i; j++)
                free(tmp.data[j]);
            free(tmp.data);
            deleteArrayOfCurrencies(&tmp.currencies);
            return MEMORY_ERROR;
        }
    }

    Offer zero_offer;
    zero_offer.bank[0] = '\0';
    zero_offer.exchange_rate = 0;
    zero_offer.bank_fee = 0;
    zero_offer.currency_pair.currency_1[0] = '\0';
    zero_offer.currency_pair.currency_2[0] = '\0';

    data->data = tmp.data;
    for (size_t i = 0; i < DEFAULT_ALLOCATED_SIZE; i++) {
        data->data[i] = tmp.data[i];
        for (size_t j = 0; j < DEFAULT_ALLOCATED_SIZE; j++)
            data->data[i][j] = zero_offer;
    }
    data->currencies = tmp.currencies;
    data->size = 0;
    data->allocated_size = DEFAULT_ALLOCATED_SIZE;

    return SUCCESS;
}

Error deleteCurrencyExchangeRates(CurrencyExchangeRates *data) {
    if ((!data->data) || (!data->allocated_size))
        return NO_DATA;

    for (size_t i = 0; i < data->allocated_size; i++)
        free(data->data[i]);
    free(data->data);
    data->data = NULL;
    data->size = 0;
    data->allocated_size = 0;
    Error err = deleteArrayOfCurrencies(&data->currencies);
    return err;
}

Error resizeCurrencyExchangeRates(CurrencyExchangeRates *data, size_t new_size) {
    if ((!data) || (!data->data) || (!data->allocated_size))
        return NO_DATA;

    CurrencyExchangeRates tmp;
    tmp.data = data->data;
    for (size_t i = 0; i < data->allocated_size; i++)
        tmp.data[i] = data->data[i];

    size_t allocated = data->allocated_size + (new_size >> 3) + (new_size < 9 ? 3 : 6);
    tmp.data = (Offer**) realloc(tmp.data, allocated * sizeof(Offer*));
    if (tmp.data)
        return MEMORY_ERROR;

    for (size_t i = 0; i < allocated; i++) {
        tmp.data[i] = (Offer *) realloc(tmp.data[i], allocated * sizeof(Offer));
        if (!tmp.data[i]) {
            for (size_t j = 0; j < i; j++)
                free(tmp.data[j]);
            free(tmp.data);
            return MEMORY_ERROR;
        }
    }

    for (size_t i = 0; i < allocated; i++)
        data->data[i] = tmp.data[i];
    data->allocated_size = allocated;

    return SUCCESS;
}

Error inputCurrencyExchangeRates(CurrencyExchangeRates *data, size_t number_of_offers) {
    Error err = SUCCESS;

    if (data->allocated_size < number_of_offers)
        err = resizeCurrencyExchangeRates(data, number_of_offers);

    for (size_t i = 0; (!err) && (i < number_of_offers); i++) {
        Offer tmp;
        err = inputOffer(&tmp);
        if (!err) {
            int newCurrency1 = 0;
            size_t row_index = find_currency_index(&data->currencies, &tmp.currency_pair.currency_1);
            if (row_index == data->currencies.size + 1) {
                appendIntoArrayOfCurrencies(&data->currencies, &tmp.currency_pair.currency_1);
                row_index = data->currencies.size - 1;
                newCurrency1 = 1;
            }

            int newCurrency2 = 0;
            size_t column_index = find_currency_index(&data->currencies, &tmp.currency_pair.currency_2);
            if (column_index == data->currencies.size + 1) {
                appendIntoArrayOfCurrencies(&data->currencies, &tmp.currency_pair.currency_2);
                column_index = data->currencies.size - 1;
                newCurrency2 = 1;
            }

            if (newCurrency1 || newCurrency2) {
                if (data->allocated_size < data->currencies.allocated_size)
                    resizeCurrencyExchangeRates(data, data->allocated_size);
                data->data[row_index][column_index] = tmp;
            }
            else {
                double first_exchange_rate;
                err = getResultExchangeRate(&data->data[row_index][column_index], &first_exchange_rate);

                double second_exchange_rate;
                if (!err)
                    err = getResultExchangeRate(&tmp, &second_exchange_rate);

                if ((!err) && (first_exchange_rate < second_exchange_rate))
                    data->data[row_index][column_index] = tmp;
            }

        }
    }

    return err;
}


Error find_best_exchange_rate(const CurrencyExchangeRates *data, const CurrencyPair *currencyPair,
                               ArrayOfOffers *strategy, double *best_exchange_rate) {

    if ((!data) || (!data->data) || (!data->allocated_size) ||
        (!currencyPair) || (!strategy) || (!best_exchange_rate))
        return NO_DATA;

    size_t begin_index = find_currency_index(&data->currencies, &currencyPair->currency_1);
    size_t end_index = find_currency_index(&data->currencies, &currencyPair->currency_2);
    if ((begin_index > data->currencies.size) || (end_index > data->currencies.size))
        return NO_DATA;


    double *d = (double*) malloc(data->currencies.size * sizeof(double));
    if (!d)
        return MEMORY_ERROR;

    size_t *v = (size_t*) malloc(data->currencies.size * sizeof(size_t));
    if (!v) {
        free(d);
        return MEMORY_ERROR;
    }

    size_t *ver = (size_t*) malloc(data->currencies.size * sizeof(size_t));
    if (!ver) {
        free(d);
        free(v);
        return MEMORY_ERROR;
    }



    for (size_t i = 0; i < data->currencies.size; i++) {
        d[i] = 0;
        v[i] = 1;
    }

    Error err = SUCCESS;
    size_t max_index;
    d[begin_index] = 1;
    do {
        max_index = data->currencies.size + 1;
        double max_rate = 0;
        for (size_t i = 0; i < data->currencies.size; i++)
            if ((v[i] == 1) && (d[i] > max_rate)) {
                max_rate = d[i];
                max_index = i;
            }

        if (max_index != data->currencies.size + 1) {
            for (size_t i = 0; ((!err) && (i < data->currencies.size)); i++) {
                double tmp;
                err = getResultExchangeRate(&data->data[max_index][i], &tmp);
                if ((tmp > 0) && (!err)) {
                    tmp *= max_rate;
                    if ((tmp > d[i]) || (!d[i]))
                        d[i] = tmp;
                }
            }
            v[max_index] = 0;
        }
    } while ((!err) && (max_index < data->currencies.size + 1));

    // Восстановление пути
    size_t end = end_index;
    ver[0] = end;
    size_t k = 1;
    double weight = d[end];

    while ((end != begin_index) && (!err))
        for (size_t i = 0; ((!err) && (i < data->currencies.size)); i++)
            if (data->data[i][end].exchange_rate) {
                double tmp;
                err = getResultExchangeRate(&data->data[i][end], &tmp);
                if (!err) {
                    tmp = weight / tmp;
                    if ((fabs(tmp - d[i]) - EPS) < 0) {
                        weight = tmp;
                        end = i;
                        ver[k] = i;
                        k++;
                    }
                }
            }

    for (size_t i = k - 1; ((!err) && (i > 0)); i--)
        err = appendIntoArrayOfOffers(strategy, &data->data[ver[i]][ver[i - 1]]);

    if (!d[end_index])
        err = NO_DATA;

    (*best_exchange_rate) = (!err) ? d[end_index] : 0;

    free(ver);
    free(d);
    free(v);
    return err;
}
