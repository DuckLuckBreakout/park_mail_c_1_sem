#include "gtest/gtest.h"
#include "Task_manager/task_manager.h"

TEST(int_array, create_int_array) {
    int_array_t arr;
    error result = create_int_array(&arr);
    EXPECT_EQ((result == SUCCESS) && (arr.buffer) && (arr.size == 0) &&
              (arr.allocated_size == DEFAULT_ALLOCATED_SIZE), true);
    delete_int_array(&arr);
}

TEST(int_array, delete_int_array) {
    int_array_t arr;
    create_int_array(&arr);
    error result;

    // Успешное удаление
    result = delete_int_array(&arr);
    EXPECT_EQ(((result == SUCCESS) && (!arr.buffer) && (!arr.size) &&
              (!arr.allocated_size)), true);

    // Удалять нечего
    result = delete_int_array(&arr);
    EXPECT_EQ((result == NO_DATA), true);
}

TEST(int_array, resize_int_array) {
    int_array_t arr;
    create_int_array(&arr);

    error result;
    // Дополнительное выделение в пустой массив
    result = resize_int_array(&arr, 5);
    EXPECT_EQ(((result == SUCCESS) &&
               (arr.allocated_size == DEFAULT_ALLOCATED_SIZE + (5 >> 3) + 3) &&
               (arr.size == 0)), true);

    // Новый размер меньше старого
    result = resize_int_array(&arr, 2);
    EXPECT_EQ((result == BAD_SIZE), true);

    delete_int_array(&arr);
}

TEST(int_array, append_into_array_of_currencies) {
    int_array_t arr;
    create_int_array(&arr);

    int buf_int = 1;
    error result;
    // Добавление в пустой
    result = append_into_int_array(&arr, buf_int);
    EXPECT_EQ(((result == SUCCESS) &&
              (arr.size == 1) && (arr.allocated_size == DEFAULT_ALLOCATED_SIZE) &&
              (arr.buffer[0] == buf_int)), true);

    // Добавление с выделением памяти
    size_t real_alloc_size = arr.allocated_size;
    arr.allocated_size = 1;
    result = append_into_int_array(&arr, buf_int);
    EXPECT_EQ(((result == SUCCESS) && (arr.size == 2) &&
              (arr.buffer[1] == buf_int)), true);
    arr.allocated_size = real_alloc_size;
    delete_int_array(&arr);
}

TEST(objects_rating, init_objects_rating) {
    error err = init_objects_rating(nullptr);
    EXPECT_EQ(err == NO_DATA, true);

    objects_rating_t rating;
    err = init_objects_rating(&rating);
    EXPECT_EQ((err == SUCCESS) && (rating.ratings[0] == 0) &&
              (rating.ratings[RATING_SIZE - 1] == 0) && (rating.ids[0] == -1) &&
              (rating.ids[RATING_SIZE - 1] == -1), true);
}

TEST(objects_rating, update_objects_rating) {
    error err = update_objects_rating(nullptr, 0, 0);
    EXPECT_EQ(err == NO_DATA, true);

    objects_rating_t rating;

    err = update_objects_rating(&rating, -1, 0);
    EXPECT_EQ(err == INCORRECT_DATA, true);

    err = update_objects_rating(&rating, 0, -1);
    EXPECT_EQ(err == INCORRECT_DATA, true);

    err = update_objects_rating(&rating, 0, 7);
    EXPECT_EQ(err == INCORRECT_DATA, true);

    init_objects_rating(&rating);
    err = update_objects_rating(&rating, 0, 2);
    EXPECT_EQ((err == SUCCESS) && (rating.ratings[0] == 2) &&
              (rating.ratings[RATING_SIZE - 1] == 0) && (rating.ids[0] == 0) &&
              (rating.ids[RATING_SIZE - 1] == -1), true);

    err = update_objects_rating(&rating, 0, 1);
    EXPECT_EQ((err == SUCCESS) && (rating.ratings[1] == 1) &&
              (rating.ratings[RATING_SIZE - 1] == 0) && (rating.ids[0] == 0) &&
              (rating.ids[RATING_SIZE - 1] == -1), true);
}

TEST(objects_rating, print_objects_rating) {
    FILE *black_hole = fopen("/dev/null", "w");
    error err = print_objects_rating(nullptr, black_hole);
    EXPECT_EQ(err == NO_DATA, true);
    objects_rating_t rating;
    init_objects_rating(&rating);
    err = print_objects_rating(&rating, black_hole);
    EXPECT_EQ(err == SUCCESS, true);
    fclose(black_hole);
}

TEST(data, fill_index_array) {
    error err = fill_index_array(nullptr);
    EXPECT_EQ(err == NO_DATA, true);

    data_t data;
    init_data(&data, "bad_data");
    err = fill_index_array(&data);
    EXPECT_EQ(err == INCORRECT_DATA, true);
    delete_data(&data);

    data.index_array.buffer = nullptr;
    strcpy(data.file_name, "data");
    err = fill_index_array(&data);
    EXPECT_EQ(err == NO_DATA, true);

    init_data(&data, "data");
    err = fill_index_array(&data);
    EXPECT_EQ(err == SUCCESS, true);

    delete_data(&data);
}

TEST(data, init_data) {
    error err;
    char file_name[FILENAME_MAX];
    strcpy(file_name, "data");
    err = init_data(nullptr, file_name);
    EXPECT_EQ(err == NO_DATA, true);

    data_t data;
    strcpy(file_name, "");
    err = init_data(&data, file_name);
    EXPECT_EQ(err == NO_DATA, true);

    strcpy(file_name, "data");
    err = init_data(&data, file_name);
    EXPECT_EQ(err == SUCCESS, true);
    delete_data(&data);
}

TEST(data, delete_data) {
    error err = delete_data(nullptr);
    EXPECT_EQ(err == NO_DATA, true);

    data_t data;
    char file_name[FILENAME_MAX];
    strcpy(file_name, "data");
    init_data(&data, file_name);
    err = delete_data(&data);
    EXPECT_EQ(err == SUCCESS, true);
}

TEST(lineal, get_object_rating_by_id_lineal) {
    error err = get_object_rating_by_id_lineal(nullptr, 0, 0, nullptr);
    EXPECT_EQ(err == NO_DATA, true);

    data_t data;
    char file_name[FILENAME_MAX];
    strcpy(file_name, "data");
    init_data(&data, file_name);

    float buf_rating = 0;

    err = get_object_rating_by_id_lineal(&data, -1, 1000, &buf_rating);
    EXPECT_EQ(err == INCORRECT_DATA, true);

    err = get_object_rating_by_id_lineal(&data, 2, -1, &buf_rating);
    EXPECT_EQ(err == INCORRECT_DATA, true);

    err = get_object_rating_by_id_lineal(&data, 2, 1000, &buf_rating);
    EXPECT_EQ((err == SUCCESS) && (buf_rating - 3.5 < EPS), true);

    buf_rating = 0;
    err = get_object_rating_by_id_lineal(&data, 34, 2, &buf_rating);
    EXPECT_EQ((err == SUCCESS) && (buf_rating < EPS), true);

    delete_data(&data);
}

TEST(lineal, get_recommendation_for_user_lineal) {
    objects_rating_t rating;
    init_objects_rating(&rating);
    error err = get_recommendation_for_user_lineal(nullptr, 1, &rating);
    EXPECT_EQ(err == NO_DATA, true);


    data_t data;
    char file_name[FILENAME_MAX];
    strcpy(file_name, "data");
    init_data(&data, file_name);

    err = get_recommendation_for_user_lineal(&data, 1, nullptr);
    EXPECT_EQ(err == NO_DATA, true);

    err = get_recommendation_for_user_lineal(&data, -1, &rating);
    EXPECT_EQ(err == INCORRECT_DATA, true);

    err = get_recommendation_for_user_lineal(&data, 3, &rating);
    for (int i = 0; i < 10; i++)
        printf("\n%d)%d", i, rating.ids[i]);
    EXPECT_EQ((err == SUCCESS) &&
              (rating.ids[0] == 76) && (rating.ids[1] == 52) &&
              (rating.ids[2] == 47) && (rating.ids[3] == 23) &&
              (rating.ids[4] == 45) && (rating.ids[5] == 22) &&
              (rating.ids[6] == 21) && (rating.ids[7] == 86) &&
              (rating.ids[8] == 51) && (rating.ids[9] == 50), true);

    delete_data(&data);
}

TEST(parallel, get_recommendation_for_user_parallel) {
    objects_rating_t rating;
    init_objects_rating(&rating);
    error err = get_recommendation_for_user_parallel(nullptr, 1, &rating);
    EXPECT_EQ(err == NO_DATA, true);


    data_t data;
    char file_name[FILENAME_MAX];
    strcpy(file_name, "data");
    init_data(&data, file_name);

    err = get_recommendation_for_user_parallel(&data, 1, nullptr);
    EXPECT_EQ(err == NO_DATA, true);

    err = get_recommendation_for_user_parallel(&data, -1, &rating);
    EXPECT_EQ(err == INCORRECT_DATA, true);

    err = get_recommendation_for_user_parallel(&data, 3, &rating);
    EXPECT_EQ((err == SUCCESS) &&
              (rating.ids[0] == 76) && (rating.ids[1] == 52) &&
              (rating.ids[2] == 47) && (rating.ids[3] == 23) &&
              (rating.ids[4] == 45) && (rating.ids[5] == 22) &&
              (rating.ids[6] == 21) && (rating.ids[7] == 86) &&
              (rating.ids[8] == 51) && (rating.ids[9] == 50), true);

    delete_data(&data);
}


TEST(errors_message, print_error_message) {

    error err = SUCCESS;
    FILE *black_hole = fopen("/dev/null", "w");
    EXPECT_NO_FATAL_FAILURE(print_error_message(err, black_hole));

    err = INPUT_ERROR;
    EXPECT_NO_FATAL_FAILURE(print_error_message(err, black_hole));

    err = NO_DATA;
    EXPECT_NO_FATAL_FAILURE(print_error_message(err, black_hole));

    err = BAD_SIZE;
    EXPECT_NO_FATAL_FAILURE(print_error_message(err, black_hole));

    err = MEMORY_ERROR;
    EXPECT_NO_FATAL_FAILURE(print_error_message(err, black_hole));

    err = INCORRECT_DATA;
    EXPECT_NO_FATAL_FAILURE(print_error_message(err, black_hole));

    fclose(black_hole);
}

TEST(task_manager, task_manager) {
    EXPECT_EQ(task_manager(nullptr) == NO_DATA, true);
}

TEST(stress_test, stress_test) {
    data_t data;

    objects_rating_t user_rating_parallel;
    init_objects_rating(&user_rating_parallel);

    objects_rating_t user_rating_lineal;
    init_objects_rating(&user_rating_lineal);

    init_data(&data, "data10");
    get_recommendation_for_user_parallel(&data, 5, &user_rating_parallel);
    get_recommendation_for_user_lineal(&data, 5, &user_rating_lineal);

    for (int i = 0; i < RATING_SIZE; i++)
        EXPECT_EQ(user_rating_parallel.ids[i] == user_rating_lineal.ids[i], true);
    delete_data(&data);

    init_data(&data, "data10000");
    get_recommendation_for_user_parallel(&data, 5, &user_rating_parallel);
    get_recommendation_for_user_lineal(&data, 5, &user_rating_lineal);

    for (int i = 0; i < RATING_SIZE; i++)
        EXPECT_EQ(user_rating_parallel.ids[i] == user_rating_lineal.ids[i], true);
    delete_data(&data);
}