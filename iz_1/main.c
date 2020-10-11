#include "Errors/error_message.h"
#include "TaskManager/task_manager.h"


int main() {
    Error err = task_manager();
    if (err)
        error_message(err);
    return err;
}
