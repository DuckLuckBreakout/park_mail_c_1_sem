#include "error_message.h"

void print_error_message(error err, FILE *target) {
    switch (err) {
        case INPUT_ERROR:
            fprintf(target, "Error: input error");
            break;
        case MEMORY_ERROR:
            fprintf(target, "Error: memory error");
            break;
        case NO_DATA:
            fprintf(target, "Error: no data");
            break;
        case BAD_SIZE:
            fprintf(target, "Error: bad size");
            break;
        case SUCCESS:
            break;
        default:
            fprintf(target, "Error: Error code %d", err);
    }
}
