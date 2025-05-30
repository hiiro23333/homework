#ifndef TIME_UTILS_H
#define TIME_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>

typedef time_t (*time_func)();

time_t current_time();
void set_current_time_function(time_func func);

#ifdef __cplusplus
}
#endif

#endif