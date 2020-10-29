#ifndef IZ_2_DATA_STRUCT_H
#define IZ_2_DATA_STRUCT_H

#include "int_array.h"

typedef struct data {
    char file_name[FILE_NAME_MAX_LEN];
    int_array_t index_array;
} data_t;

#endif //IZ_2_DATA_STRUCT_H
