#ifndef IZ_2_DATA_H
#define IZ_2_DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "user_mark.h"
#include "int_array.h"
#include "object.h"
#include "objects_rating.h"
#include "data_struct.h"


error fill_index_array(data_t *data);
error init_data(data_t *data, const char file_name[FILENAME_MAX]);
error delete_data(data_t *data);


#endif //IZ_2_DATA_H
