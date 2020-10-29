#ifndef IZ_2_OBJECT_H
#define IZ_2_OBJECT_H

#include "object_name.h"

typedef struct object_t {
    int id;
    int marks_count;
    object_name_t name;
} object_t;

#endif //IZ_2_OBJECT_H
