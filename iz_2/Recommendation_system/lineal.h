#ifndef IZ_2_LINEAL_H
#define IZ_2_LINEAL_H

#include "data.h"

error get_object_rating_by_id_lineal(data_t *data, int obj_id, int user_id, float *obj_rating);
error get_recommendation_for_user_lineal(data_t *data, int user_id, objects_rating_t *user_rating);

#endif //IZ_2_LINEAL_H
