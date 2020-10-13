#include "currency_exchange_rates.h"

error_t create_currency_exchange_rates(currency_exchange_rates_t *data) {
    currency_exchange_rates_t buf_currency_exchange_rates;
    error_t err = create_array_of_currencies(&buf_currency_exchange_rates.currencies);
    if (err)
        return MEMORY_ERROR;

    buf_currency_exchange_rates.data = (offer_t**) malloc(DEFAULT_ALLOCATED_SIZE * sizeof(offer_t*));
    if (!buf_currency_exchange_rates.data) {
        delete_array_of_currencies(&buf_currency_exchange_rates.currencies);
        return MEMORY_ERROR;
    }

    for (size_t i = 0; (i < DEFAULT_ALLOCATED_SIZE); i++) {
        buf_currency_exchange_rates.data[i] = (offer_t*) malloc(DEFAULT_ALLOCATED_SIZE * sizeof(offer_t));
        if (!buf_currency_exchange_rates.data[i]) {
            for (size_t j = 0; j < i; j++)
                free(buf_currency_exchange_rates.data[j]);
            free(buf_currency_exchange_rates.data);
            delete_array_of_currencies(&buf_currency_exchange_rates.currencies);
            return MEMORY_ERROR;
        }
    }

    offer_t zero_offer;
    zero_offer.bank[0] = '\0';
    zero_offer.exchange_rate = 0;
    zero_offer.bank_fee = 0;
    zero_offer.currency_pair.currency_1[0] = '\0';
    zero_offer.currency_pair.currency_2[0] = '\0';

    data->data = buf_currency_exchange_rates.data;
    for (size_t i = 0; i < DEFAULT_ALLOCATED_SIZE; i++) {
        data->data[i] = buf_currency_exchange_rates.data[i];
        for (size_t j = 0; j < DEFAULT_ALLOCATED_SIZE; j++)
            data->data[i][j] = zero_offer;
    }
    data->currencies = buf_currency_exchange_rates.currencies;
    data->size = 0;
    data->allocated_size = DEFAULT_ALLOCATED_SIZE;

    return SUCCESS;
}

error_t delete_currency_exchange_rates(currency_exchange_rates_t *data) {
    if ((!data->data) || (!data->allocated_size))
        return NO_DATA;

    for (size_t i = 0; i < data->allocated_size; i++)
        free(data->data[i]);
    free(data->data);
    data->data = NULL;
    data->size = 0;
    data->allocated_size = 0;
    error_t err = delete_array_of_currencies(&data->currencies);
    return err;
}

error_t resize_currency_exchange_rates(currency_exchange_rates_t *data, size_t new_size) {
    if ((!data) || (!data->data) || (!data->allocated_size))
        return NO_DATA;

    currency_exchange_rates_t buf_currency_exchange_rates;
    buf_currency_exchange_rates.data = data->data;
    for (size_t i = 0; i < data->allocated_size; i++)
        buf_currency_exchange_rates.data[i] = data->data[i];

    size_t allocated = data->allocated_size + (new_size >> 3) + (new_size < 9 ? 3 : 6);
    buf_currency_exchange_rates.data = (offer_t**) realloc(buf_currency_exchange_rates.data,
                                                         allocated * sizeof(offer_t*));
    if (!buf_currency_exchange_rates.data)
        return MEMORY_ERROR;

    for (size_t i = 0; i < allocated; i++) {
        buf_currency_exchange_rates.data[i] = (offer_t*) realloc(buf_currency_exchange_rates.data[i],
                                                               allocated * sizeof(offer_t));
        if (!buf_currency_exchange_rates.data[i]) {
            for (size_t j = 0; j < i; j++)
                free(buf_currency_exchange_rates.data[j]);
            free(buf_currency_exchange_rates.data);
            return MEMORY_ERROR;
        }
    }

    for (size_t i = 0; i < allocated; i++)
        data->data[i] = buf_currency_exchange_rates.data[i];
    data->allocated_size = allocated;

    return SUCCESS;
}

error_t input_currency_exchange_rates(currency_exchange_rates_t *data, size_t number_of_offers) {
    error_t err = SUCCESS;

    if (data->allocated_size < number_of_offers)
        err = resize_currency_exchange_rates(data, number_of_offers);

    for (size_t i = 0; (!err) && (i < number_of_offers); i++) {
        offer_t buf_offer;
        err = input_offer(&buf_offer);
        if (!err) {
            int newCurrency1 = 0;
            size_t row_index = find_currency_index(&data->currencies,
                                                   &buf_offer.currency_pair.currency_1);
            if (row_index == data->currencies.size + 1) {
                append_into_array_of_currencies(&data->currencies,
                                                &buf_offer.currency_pair.currency_1);
                row_index = data->currencies.size - 1;
                newCurrency1 = 1;

                data->size++;
            }

            int newCurrency2 = 0;
            size_t column_index = find_currency_index(&data->currencies,
                                                      &buf_offer.currency_pair.currency_2);
            if (column_index == data->currencies.size + 1) {
                append_into_array_of_currencies(&data->currencies,
                                                &buf_offer.currency_pair.currency_2);
                column_index = data->currencies.size - 1;
                newCurrency2 = 1;

                data->size++;
            }

            if (newCurrency1 || newCurrency2) {
                if (data->allocated_size < data->currencies.allocated_size)
                    resize_currency_exchange_rates(data, data->allocated_size);
                data->data[row_index][column_index] = buf_offer;
            }
            else {
                double first_exchange_rate;
                err = get_result_exchange_rate(&data->data[row_index][column_index],
                                               &first_exchange_rate);

                double second_exchange_rate;
                if (!err)
                    err = get_result_exchange_rate(&buf_offer, &second_exchange_rate);

                if ((!err) && (first_exchange_rate < second_exchange_rate))
                    data->data[row_index][column_index] = buf_offer;
            }

        }
    }

    return err;
}


error_t dijkstra_algorithm_step(const currency_exchange_rates_t *data,
                                double *distances, size_t *not_visited_nodes,
                                size_t *max_index) {
    (*max_index) = data->currencies.size + 1;
    double max_rate = 0;
    for (size_t i = 0; i < data->currencies.size; i++)
        if ((not_visited_nodes[i] == 1) && (distances[i] > max_rate)) {
            max_rate = distances[i];
            (*max_index) = i;
        }

    error_t err = SUCCESS;
    if ((*max_index) != data->currencies.size + 1) {
        for (size_t i = 0; ((!err) && (i < data->currencies.size)); i++) {
            double exchange_rate;
            err = get_result_exchange_rate(&data->data[(*max_index)][i], &exchange_rate);
            if ((!err) && (exchange_rate > 0))
                exchange_rate *= max_rate;

            if ((!err) && ((exchange_rate > distances[i]) || (!distances[i])))
                distances[i] = exchange_rate;
        }
        not_visited_nodes[(*max_index)] = 0;
    }
    return err;
}

error_t restore_path_step(const currency_exchange_rates_t *data, size_t *end,
                          double *distances, size_t *visited_nodes,
                          size_t *last_node_index, double *weight) {
    error_t err = SUCCESS;
    for (size_t i = 0; ((!err) && (i < data->currencies.size)); i++)
        if (data->data[i][(*end)].exchange_rate) {
            double exchange_rate;
            err = get_result_exchange_rate(&data->data[i][(*end)], &exchange_rate);
            if (!err) {
                exchange_rate = (*weight) / exchange_rate;
                if ((fabs(exchange_rate - distances[i]) - EPS) < 0) {
                    (*weight) = exchange_rate;
                    (*end) = i;
                    visited_nodes[(*last_node_index)] = i;
                    (*last_node_index)++;
                }
            }
        }
    return err;
}

error_t find_best_exchange_rate(const currency_exchange_rates_t *data,
                                const currency_pair_t *currencyPair,
                                array_of_offers_t *strategy,
                                double *best_exchange_rate) {

    if ((!data) || (!data->data) || (!data->allocated_size) ||
        (!currencyPair) || (!strategy) || (!best_exchange_rate))
        return NO_DATA;

    size_t begin_index = find_currency_index(&data->currencies,
                                             &currencyPair->currency_1);
    size_t end_index = find_currency_index(&data->currencies,
                                           &currencyPair->currency_2);

    if ((begin_index > data->currencies.size) ||
        (end_index > data->currencies.size))
        return NO_DATA;


    double *distances = (double*) malloc(data->currencies.size * sizeof(double));
    if (!distances)
        return MEMORY_ERROR;

    size_t *not_visited_nodes = (size_t*) malloc(data->currencies.size * sizeof(size_t));
    if (!not_visited_nodes) {
        free(distances);
        return MEMORY_ERROR;
    }

    size_t *visited_nodes = (size_t*) malloc(data->currencies.size * sizeof(size_t));
    if (!visited_nodes) {
        free(distances);
        free(not_visited_nodes);
        return MEMORY_ERROR;
    }


    for (size_t i = 0; i < data->currencies.size; i++) {
        distances[i] = 0;
        not_visited_nodes[i] = 1;
    }

    error_t err = SUCCESS;
    size_t max_index;
    distances[begin_index] = 1;
    do {
        err = dijkstra_algorithm_step(data, distances, not_visited_nodes, &max_index);
    } while ((!err) && (max_index < data->currencies.size + 1));

    // Восстановление пути
    size_t end = end_index;
    visited_nodes[0] = end;
    size_t last_node_index = 1;
    double weight = distances[end];

    while ((end != begin_index) && (!err)) {
        err = restore_path_step(data, &end, distances, visited_nodes, &last_node_index, &weight);
    }

    for (size_t i = last_node_index - 1; ((!err) && (i > 0)); i--)
        err = append_into_array_of_offers(strategy, &data->data[visited_nodes[i]][visited_nodes[i - 1]]);

    if (!distances[end_index])
        err = NO_DATA;

    (*best_exchange_rate) = (!err) ? distances[end_index] : 0;

    free(visited_nodes);
    free(distances);
    free(not_visited_nodes);
    return err;
}
