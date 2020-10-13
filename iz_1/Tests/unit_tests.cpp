#include <cmath>
#include "gtest/gtest.h"
#include "Task_manager/task_manager.h"


TEST(currency_pair, is_equal_currency_pairs) {
    currency_pair_t first, second;

    // Равны
    strcpy(first.currency_1, "USD");
    strcpy(first.currency_2, "RUB");
    strcpy(second.currency_1, "USD");
    strcpy(second.currency_2, "RUB");
    EXPECT_EQ(is_equal_currency_pairs(&first, &second), true);

    //Не равны
    strcpy(second.currency_1, "EUR");
    EXPECT_EQ(is_equal_currency_pairs(&first, &second), false);

}

TEST(offer, get_result_exchange_rate){
    offer_t offer;
    strcpy(offer.bank, "test");
    strcpy(offer.currency_pair.currency_1, "USD");
    strcpy(offer.currency_pair.currency_2, "RUB");
    offer.bank_fee = 0.02;
    offer.exchange_rate = 90;

    double result;
    error_t err = get_result_exchange_rate(&offer, &result);
    EXPECT_EQ((fabs(result - 88.2) < EPS) && (!err), true);
}

TEST(array_of_offers, create_array_of_offers){
    array_of_offers_t arr;
    error_t result = create_array_of_offers(&arr);
    EXPECT_EQ((result == SUCCESS) && (arr.data) && (arr.size == 0) &&
              (arr.allocated_size == DEFAULT_ALLOCATED_SIZE), true);
    delete_array_of_offers(&arr);
}

TEST(array_of_offers, delete_array_of_offers){
    array_of_offers_t arr;
    create_array_of_offers(&arr);
    error_t result;

    // Успешное удаление
    result = delete_array_of_offers(&arr);
    EXPECT_EQ((result == SUCCESS) && (!arr.data) && (!arr.size) &&
              (!arr.allocated_size), true);

    // Удалять нечего
    result = delete_array_of_offers(&arr);
    EXPECT_EQ((result == NO_DATA), true);
}

TEST(array_of_offers, resize_array_of_offers){
    array_of_offers_t arr;
    create_array_of_offers(&arr);

    error_t result;
    // Дополнительное выделение в пустой массив
    result = resize_array_of_offers(&arr, 5);
    EXPECT_EQ(((result == SUCCESS) &&
              (arr.allocated_size == DEFAULT_ALLOCATED_SIZE + (5 >> 3) + 3) &&
              (arr.size == 0)), true);

    // Новый размер меньше старого
    result = resize_array_of_offers(&arr, 2);
    EXPECT_EQ((result == BAD_SIZE), true);

    delete_array_of_offers(&arr);
}

TEST(array_of_offers, append_into_array_of_offers){
    array_of_offers_t arr;
    create_array_of_offers(&arr);

    offer_t offer;
    strcpy(offer.bank, "test");
    strcpy(offer.currency_pair.currency_1, "USD");
    strcpy(offer.currency_pair.currency_2, "RUB");
    offer.bank_fee = 0.02;
    offer.exchange_rate = 90;

    error_t result;
    // Добавление в пустой
    result = append_into_array_of_offers(&arr, &offer);
    EXPECT_EQ((result == SUCCESS) &&
              (arr.size == 1) && (arr.allocated_size == DEFAULT_ALLOCATED_SIZE) &&
              (!strcmp(arr.data[0].bank, offer.bank) )&&
              (arr.data[0].bank_fee == offer.bank_fee) &&
              (arr.data[0].exchange_rate == offer.exchange_rate) &&
              (is_equal_currency_pairs(&arr.data[0].currency_pair,
                                       &offer.currency_pair)), true);

    // Добавление с выделением памяти
    size_t real_alloc_size = arr.allocated_size;
    arr.allocated_size = 1;
    result = append_into_array_of_offers(&arr, &offer);
    EXPECT_EQ(((result == SUCCESS) && (arr.size == 2) &&
              (!strcmp(arr.data[1].bank, offer.bank) )&&
              (arr.data[1].bank_fee == offer.bank_fee) &&
              (arr.data[1].exchange_rate == offer.exchange_rate) &&
              (is_equal_currency_pairs(&arr.data[1].currency_pair, &offer.currency_pair))), true);
    arr.allocated_size = real_alloc_size;
    delete_array_of_offers(&arr);
}

TEST(array_of_currencies, create_array_of_currencies){
    array_of_currencies_t arr;
    error_t result = create_array_of_currencies(&arr);
    EXPECT_EQ((result == SUCCESS) && (arr.data) && (arr.size == 0) &&
              (arr.allocated_size == DEFAULT_ALLOCATED_SIZE), true);
    delete_array_of_currencies(&arr);
}

TEST(array_of_currencies, delete_array_of_currencies){
    array_of_currencies_t arr;
    create_array_of_currencies(&arr);
    error_t result;

    // Успешное удаление
    result = delete_array_of_currencies(&arr);
    EXPECT_EQ(((result == SUCCESS) && (!arr.data) && (!arr.size) &&
              (!arr.allocated_size)), true);

    // Удалять нечего
    result = delete_array_of_currencies(&arr);
    EXPECT_EQ((result == NO_DATA), true);
}

TEST(array_of_currencies, resize_array_of_currencies){
    array_of_currencies_t arr;
    create_array_of_currencies(&arr);

    error_t result;
    // Дополнительное выделение в пустой массив
    result = resize_array_of_currencies(&arr, 5);
    EXPECT_EQ(((result == SUCCESS) &&
               (arr.allocated_size == DEFAULT_ALLOCATED_SIZE + (5 >> 3) + 3) &&
               (arr.size == 0)), true);

    // Новый размер меньше старого
    result = resize_array_of_currencies(&arr, 2);
    EXPECT_EQ((result == BAD_SIZE), true);

    delete_array_of_currencies(&arr);
}

TEST(array_of_currencies, append_into_array_of_currencies){
    array_of_currencies_t arr;
    create_array_of_currencies(&arr);

    currency_t currency;
    strcpy(currency, "USD");

    error_t result;
    // Добавление в пустой
    result = append_into_array_of_currencies(&arr, &currency);
    EXPECT_EQ(((result == SUCCESS) &&
              (arr.size == 1) && (arr.allocated_size == DEFAULT_ALLOCATED_SIZE) &&
              (!strcmp(arr.data[0], currency))), true);

    // Добавление с выделением памяти
    size_t real_alloc_size = arr.allocated_size;
    arr.allocated_size = 1;
    result = append_into_array_of_currencies(&arr, &currency);
    EXPECT_EQ(((result == SUCCESS) && (arr.size == 2) &&
               (!strcmp(arr.data[1], currency))), true);
    arr.allocated_size = real_alloc_size;
    delete_array_of_currencies(&arr);
}

TEST(array_of_currencies, find_currency_index){
    array_of_currencies_t arr;
    create_array_of_currencies(&arr);

    currency_t currency;
    strcpy(currency, "USD");

    size_t index;

    // Поиск в пустом массиве
    index = find_currency_index(&arr, &currency);
    EXPECT_EQ(index == arr.size + 1, true);

    // Поиск элемента под индексом 1
    append_into_array_of_currencies(&arr, &currency);
    strcpy(currency, "RUB");
    append_into_array_of_currencies(&arr, &currency);

    index = find_currency_index(&arr, &currency);
    EXPECT_EQ(index == 1, true);

    // Элемента нет в массиве
    strcpy(currency, "EUR");
    index = find_currency_index(&arr, &currency);
    EXPECT_EQ(index == arr.size + 1, true);

    delete_array_of_currencies(&arr);
}

TEST(currency_exchange_rates, create_currency_exchange_rates){
    currency_exchange_rates_t data;
    error_t result = create_currency_exchange_rates(&data);
    EXPECT_EQ((result == SUCCESS) && (data.data) && (data.size == 0) &&
              (data.currencies.data) && (data.currencies.size == 0) &&
              (data.currencies.allocated_size == DEFAULT_ALLOCATED_SIZE) &&
              (data.allocated_size == DEFAULT_ALLOCATED_SIZE), true);
    delete_currency_exchange_rates(&data);
}

TEST(currency_exchange_rates, delete_currency_exchange_rates){
    currency_exchange_rates_t data;
    create_currency_exchange_rates(&data);
    error_t result;

    // Успешное удаление
    result = delete_currency_exchange_rates(&data);
    EXPECT_EQ(((result == SUCCESS) && (!data.data) && (!data.size) &&
               (!data.allocated_size) && (!data.currencies.data) &&
               (!data.currencies.allocated_size)), true);

    // Удалять нечего
    result = delete_currency_exchange_rates(&data);
    EXPECT_EQ((result == NO_DATA), true);
}

TEST(currency_exchange_rates, find_best_exchange_rate){

    currency_exchange_rates_t data;
    // Путь есть
    create_currency_exchange_rates(&data);
    strcpy(data.currencies.data[0], "USD");
    strcpy(data.currencies.data[1], "EUR");
    strcpy(data.currencies.data[2], "RUB");
    data.currencies.size = 3;

    offer_t offer;
    strcpy(offer.bank, "Tinkoff");
    strcpy(offer.currency_pair.currency_1, "USD");
    strcpy(offer.currency_pair.currency_2, "EUR");
    offer.exchange_rate = 0.85;
    offer.bank_fee = 0.01;
    data.data[0][1] = offer;

    strcpy(offer.bank, "Sber");
    strcpy(offer.currency_pair.currency_1, "EUR");
    strcpy(offer.currency_pair.currency_2, "USD");
    offer.exchange_rate = 1.01;
    offer.bank_fee = 0.2;
    data.data[1][0] = offer;


    strcpy(offer.bank, "Alpha");
    strcpy(offer.currency_pair.currency_1, "EUR");
    strcpy(offer.currency_pair.currency_2, "RUB");
    offer.exchange_rate = 95;
    offer.bank_fee = 0.05;
    data.data[1][2] = offer;

    currency_pair_t pair;
    strcpy(pair.currency_1, "USD");
    strcpy(pair.currency_2, "RUB");


    double result;
    array_of_offers_t arr;
    create_array_of_offers(&arr);
    error_t err = find_best_exchange_rate(&data, &pair, &arr, &result);
    EXPECT_EQ((fabs(result - 75.945375) < EPS) && (!err), true);

    // Валюты нет в списке
    strcpy(pair.currency_1, "USD");
    strcpy(pair.currency_2, "GKY");

    err = find_best_exchange_rate(&data, &pair, &arr, &result);
    EXPECT_EQ(err == NO_DATA, true);

    delete_array_of_offers(&arr);
    delete_currency_exchange_rates(&data);
}
