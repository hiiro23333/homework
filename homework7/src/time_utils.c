#include "time_utils.h"

static time_func current_time_func = NULL;

time_t current_time() {
    if (current_time_func) {
        return current_time_func();
    }
    return time(NULL);
}

void set_current_time_function(time_func func) {
    current_time_func = func;
}