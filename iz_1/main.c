#include "Errors/error_message.h"
#include "Task_manager/task_manager.h"


int main() {
    Error err = task_manager();
    if (err)
        print_error_message(err);
    return err;
}
