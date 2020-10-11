#include <cmath>
#include "gtest/gtest.h"
#include "../TaskManager/task_manager.h"


TEST(CurrencyPair, isEqualCurrencyPair) {
    CurrencyPair first, second;

    // Равны
    strcpy(first.currency_1, "USD");
    strcpy(first.currency_2, "RUB");
    strcpy(second.currency_1, "USD");
    strcpy(second.currency_2, "RUB");
    EXPECT_EQ(isEqualCurrencyPair(&first, &second), true);

    //Не равны
    strcpy(second.currency_1, "EUR");
    EXPECT_EQ(isEqualCurrencyPair(&first, &second), false);

}

TEST(ArrayOfOffers, getResultExchangeRate){
    Offer offer;
    strcpy(offer.bank, "test");
    strcpy(offer.currency_pair.currency_1, "USD");
    strcpy(offer.currency_pair.currency_2, "RUB");
    offer.bank_fee = 0.02;
    offer.exchange_rate = 90;

    double result;
    Error err = getResultExchangeRate(&offer, &result);
    EXPECT_EQ((fabs(result - 88.2) < EPS) && (!err), true);
}

TEST(ArrayOfOffers, createArrayOfOffers){
    ArrayOfOffers arr;
    Error result = createArrayOfOffers(&arr);
    EXPECT_EQ((result == SUCCESS) && (arr.data) && (arr.size == 0) &&
             (arr.allocated_size == DEFAULT_ALLOCATED_SIZE), true);
    deleteArrayOfOffers(&arr);
}

TEST(ArrayOfOffers, deleteArrayOfOffers){
    ArrayOfOffers arr;
    createArrayOfOffers(&arr);
    Error result;

    // Успешное удаление
    result = deleteArrayOfOffers(&arr);
    EXPECT_EQ((result == SUCCESS) && (!arr.data) && (!arr.size) &&
              (!arr.allocated_size), true);

    // Удалять нечего
    result = deleteArrayOfOffers(&arr);
    EXPECT_EQ((result == NO_DATA), true);
}

TEST(ArrayOfOffers, resizeArrayOfOffers){
    ArrayOfOffers arr;
    createArrayOfOffers(&arr);

    Error result;
    // Дополнительное выделение в пустой массив
    result = resizeArrayOfOffers(&arr, 5);
    EXPECT_EQ(((result == SUCCESS) &&
              (arr.allocated_size == DEFAULT_ALLOCATED_SIZE + (5 >> 3) + 3) &&
              (arr.size == 0)), true);

    // Новый размер меньше старого
    result = resizeArrayOfOffers(&arr, 2);
    EXPECT_EQ((result == BAD_SIZE), true);

    deleteArrayOfOffers(&arr);
}

TEST(ArrayOfOffers, appendIntoArrayOfOffers){
    ArrayOfOffers arr;
    createArrayOfOffers(&arr);

    Offer offer;
    strcpy(offer.bank, "test");
    strcpy(offer.currency_pair.currency_1, "USD");
    strcpy(offer.currency_pair.currency_2, "RUB");
    offer.bank_fee = 0.02;
    offer.exchange_rate = 90;

    Error result;
    // Добавление в пустой
    result = appendIntoArrayOfOffers(&arr, &offer);
    EXPECT_EQ((result == SUCCESS) &&
              (arr.size == 1) && (arr.allocated_size == DEFAULT_ALLOCATED_SIZE) &&
              (!strcmp(arr.data[0].bank, offer.bank) )&&
              (arr.data[0].bank_fee == offer.bank_fee) &&
              (arr.data[0].exchange_rate == offer.exchange_rate) &&
              (isEqualCurrencyPair(&arr.data[0].currency_pair, &offer.currency_pair)), true);

    // Добавление с выделением памяти
    size_t real_alloc_size = arr.allocated_size;
    arr.allocated_size = 1;
    result = appendIntoArrayOfOffers(&arr, &offer);
    EXPECT_EQ(((result == SUCCESS) && (arr.size == 2) &&
              (!strcmp(arr.data[1].bank, offer.bank) )&&
              (arr.data[1].bank_fee == offer.bank_fee) &&
              (arr.data[1].exchange_rate == offer.exchange_rate) &&
              (isEqualCurrencyPair(&arr.data[1].currency_pair, &offer.currency_pair))), true);
    arr.allocated_size = real_alloc_size;
    deleteArrayOfOffers(&arr);
}

TEST(ArrayOfCurrencies, createArrayOfCurrencies){
    ArrayOfCurrencies arr;
    Error result = createArrayOfCurrencies(&arr);
    EXPECT_EQ((result == SUCCESS) && (arr.data) && (arr.size == 0) &&
              (arr.allocated_size == DEFAULT_ALLOCATED_SIZE), true);
    deleteArrayOfCurrencies(&arr);
}

TEST(ArrayOfCurrencies, deleteArrayOfCurrencies){
    ArrayOfCurrencies arr;
    createArrayOfCurrencies(&arr);
    Error result;

    // Успешное удаление
    result = deleteArrayOfCurrencies(&arr);
    EXPECT_EQ(((result == SUCCESS) && (!arr.data) && (!arr.size) &&
              (!arr.allocated_size)), true);

    // Удалять нечего
    result = deleteArrayOfCurrencies(&arr);
    EXPECT_EQ((result == NO_DATA), true);
}

TEST(ArrayOfCurrencies, resizeArrayOfCurrencies){
    ArrayOfCurrencies arr;
    createArrayOfCurrencies(&arr);

    Error result;
    // Дополнительное выделение в пустой массив
    result = resizeArrayOfCurrencies(&arr, 5);
    EXPECT_EQ(((result == SUCCESS) &&
               (arr.allocated_size == DEFAULT_ALLOCATED_SIZE + (5 >> 3) + 3) &&
               (arr.size == 0)), true);

    // Новый размер меньше старого
    result = resizeArrayOfCurrencies(&arr, 2);
    EXPECT_EQ((result == BAD_SIZE), true);

    deleteArrayOfCurrencies(&arr);
}

TEST(ArrayOfCurrencies, appendArrayOfCurrencies){
    ArrayOfCurrencies arr;
    createArrayOfCurrencies(&arr);

    Currency currency;
    strcpy(currency, "USD");

    Error result;
    // Добавление в пустой
    result = appendIntoArrayOfCurrencies(&arr, &currency);
    EXPECT_EQ(((result == SUCCESS) &&
              (arr.size == 1) && (arr.allocated_size == DEFAULT_ALLOCATED_SIZE) &&
              (!strcmp(arr.data[0], currency))), true);

    // Добавление с выделением памяти
    size_t real_alloc_size = arr.allocated_size;
    arr.allocated_size = 1;
    result = appendIntoArrayOfCurrencies(&arr, &currency);
    EXPECT_EQ(((result == SUCCESS) && (arr.size == 2) &&
               (!strcmp(arr.data[1], currency))), true);
    arr.allocated_size = real_alloc_size;
    deleteArrayOfCurrencies(&arr);
}

TEST(ArrayOfCurrencies, find_currency_index){
    ArrayOfCurrencies arr;
    createArrayOfCurrencies(&arr);

    Currency currency;
    strcpy(currency, "USD");

    size_t index;

    // Поиск в пустом массиве
    index = find_currency_index(&arr, &currency);
    EXPECT_EQ(index == arr.size + 1, true);

    // Поиск элемента под индексом 1
    appendIntoArrayOfCurrencies(&arr, &currency);
    strcpy(currency, "RUB");
    appendIntoArrayOfCurrencies(&arr, &currency);

    index = find_currency_index(&arr, &currency);
    EXPECT_EQ(index == 1, true);

    // Элемента нет в массиве
    strcpy(currency, "EUR");
    index = find_currency_index(&arr, &currency);
    EXPECT_EQ(index == arr.size + 1, true);

    deleteArrayOfCurrencies(&arr);
}

TEST(CurrencyExchangeRates, createCurrencyExchangeRates){
    CurrencyExchangeRates data;
    Error result = createCurrencyExchangeRates(&data);
    EXPECT_EQ((result == SUCCESS) && (data.data) && (data.size == 0) &&
              (data.currencies.data) && (data.currencies.size == 0) &&
              (data.currencies.allocated_size == DEFAULT_ALLOCATED_SIZE) &&
              (data.allocated_size == DEFAULT_ALLOCATED_SIZE), true);
    deleteCurrencyExchangeRates(&data);
}

TEST(CurrencyExchangeRates, deleteCurrencyExchangeRates){
    CurrencyExchangeRates data;
    createCurrencyExchangeRates(&data);
    Error result;

    // Успешное удаление
    result = deleteCurrencyExchangeRates(&data);
    EXPECT_EQ(((result == SUCCESS) && (!data.data) && (!data.size) &&
               (!data.allocated_size) && (!data.currencies.data) &&
               (!data.currencies.allocated_size)), true);

    // Удалять нечего
    result = deleteCurrencyExchangeRates(&data);
    EXPECT_EQ((result == NO_DATA), true);
}

TEST(CurrencyExchangeRates, find_best_exchange_rate){

    CurrencyExchangeRates data;
    // Путь есть
    createCurrencyExchangeRates(&data);
    strcpy(data.currencies.data[0], "USD");
    strcpy(data.currencies.data[1], "EUR");
    strcpy(data.currencies.data[2], "RUB");
    data.currencies.size = 3;

    Offer offer;
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

    CurrencyPair pair;
    strcpy(pair.currency_1, "USD");
    strcpy(pair.currency_2, "RUB");


    double result;
    ArrayOfOffers arr;
    createArrayOfOffers(&arr);
    Error err = find_best_exchange_rate(&data, &pair, &arr, &result);
    EXPECT_EQ((fabs(result - 75.945375) < EPS) && (!err), true);

    // Валюты нет в списке
    strcpy(pair.currency_1, "USD");
    strcpy(pair.currency_2, "GKY");

    err = find_best_exchange_rate(&data, &pair, &arr, &result);
    EXPECT_EQ(err == NO_DATA, true);

    deleteArrayOfOffers(&arr);
    deleteCurrencyExchangeRates(&data);
}
