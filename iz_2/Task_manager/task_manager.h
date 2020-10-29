#ifndef IZ_1_TASK_MANAGER_H
#define IZ_1_TASK_MANAGER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "Recommendation_system/data.h"
#include "Recommendation_system/parallel.h"
#include "Recommendation_system/lineal.h"
#include "Errors/error_codes.h"
#include "Errors/error_message.h"
#include "Task_flags/task_flags.h"


error task_manager(task_flags_t *task_flags);

#ifdef __cplusplus
}
#endif

#endif //IZ_1_TASK_MANAGER_H
