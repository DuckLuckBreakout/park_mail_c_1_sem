#ifndef IZ_2_TASK_FLAGS_H
#define IZ_2_TASK_FLAGS_H

#include <stdio.h>

typedef struct task_flags {
    int user_id;
    int parallel;
    char source[FILENAME_MAX];
    char target[FILENAME_MAX];
} task_flags_t;

#endif //IZ_2_TASK_FLAGS_H
