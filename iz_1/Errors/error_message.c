#include "error_message.h"

void print_error_message(error err) {
    switch (err) {
        case INPUT_ERROR:
            printf("Error: input error");
            break;
        case MEMORY_ERROR:
            printf("Error: memory error");
            break;
        case NO_DATA:
            printf("Error: no data");
            break;
        case BAD_SIZE:
            printf("Error: bad size");
            break;
        case SUCCESS:
            break;
        default:
            printf("Error: Error code %d", err);
    }
}
