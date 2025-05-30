#ifndef LOGGER_H
#define LOGGER_H

#ifdef __cplusplus
extern "C" {
#endif

#define LOG_MSG_MAX_LEN 256

typedef enum {
    LOG_MODE_NORMAL,
    LOG_MODE_FILTER
} LogMode;

void set_log_mode(LogMode mode);
void log_message(const char *msg);

#ifdef __cplusplus
}
#endif

#endif
