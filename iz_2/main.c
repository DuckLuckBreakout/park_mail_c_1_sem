#include <getopt.h>
#include "Task_manager/task_manager.h"
#include "Errors/error_message.h"

struct option options[] = {
        { "user_id",  required_argument, NULL,           'u' },
        { "parallel",  required_argument, NULL,           'p' },
        { "source",     required_argument, NULL,           's' },
        { "target",     required_argument, NULL,           't' },
        { NULL,        0,                 NULL,            0  }
};

int main(int argc, char** argv) {
    task_flags_t task_flags = {-1, 0};
    strcpy(task_flags.source, "data");
    strcpy(task_flags.target, "STDOUT");
    int c, opt_index;
    while ((c = getopt_long(argc, argv, "-:u:p:st", options, &opt_index)) != -1) {
        switch (c) {
            case 'u':
                task_flags.user_id = atoi(optarg);
                break;

            case 'p':
                task_flags.parallel = atoi(optarg);
                break;

            case 's':
                strcpy(task_flags.source, optarg);
                break;

            case 't':
                strcpy(task_flags.target, optarg);
                break;
        }
    }

    error err = task_manager(&task_flags);
    if (err)
        print_error_message(err, stderr);

    return err;
}
