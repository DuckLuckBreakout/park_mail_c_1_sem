#ifndef IZ_2_INT_ARRAY_H
#define IZ_2_INT_ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "Errors/error_codes.h"

typedef struct int_array {
    int *buffer;
    int size;
    int allocated_size;
} int_array_t;

error create_int_array(int_array_t *arr);
error delete_int_array(int_array_t *arr);
error resize_int_array(int_array_t *arr, int new_size);
error append_into_int_array(int_array_t *arr, int val);

#endif //IZ_2_INT_ARRAY_H
