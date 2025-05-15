#include <stdio.h>
#include <string.h>
#include <time.h>
#include "logger.h"
#include "time_utils.h"

#define MAX_LOG_ENTRIES 1024
#define ONE_HOUR_SECONDS 3600
#define ONE_MINUTE_SECONDS 60

typedef struct {
    char msg[LOG_MSG_MAX_LEN];
    time_t timestamps[120]; // 保存最多120次出现的时间
    int count;
    int flood_mode;
    time_t last_print_time;
} LogEntry;

static LogMode current_mode = LOG_MODE_NORMAL;
static LogEntry log_entries[MAX_LOG_ENTRIES];
static int log_entry_count = 0;

void set_log_mode(LogMode mode) {
    current_mode = mode;
}

static LogEntry* find_or_create_entry(const char *msg) {
    for (int i = 0; i < log_entry_count; ++i) {
        if (strcmp(log_entries[i].msg, msg) == 0) {
            return &log_entries[i];
        }
    }
    if (log_entry_count < MAX_LOG_ENTRIES) {
        strncpy(log_entries[log_entry_count].msg, msg, LOG_MSG_MAX_LEN - 1);
        log_entries[log_entry_count].count = 0;
        log_entries[log_entry_count].flood_mode = 0;
        log_entries[log_entry_count].last_print_time = 0;
        return &log_entries[log_entry_count++];
    }
    return NULL;
}

static int count_recent_occurrences(LogEntry *entry, time_t now, int seconds) {
    int count = 0;
    for (int i = 0; i < entry->count; ++i) {
        if (difftime(now, entry->timestamps[i]) <= seconds)
            count++;
    }
    return count;
}

void log_message(const char *msg) {
    time_t now = current_time();
    LogEntry *entry = find_or_create_entry(msg);
    if (!entry) return;

    // 清除过期的时间戳
    int new_count = 0;
    for (int i = 0; i < entry->count; ++i) {
        if (difftime(now, entry->timestamps[i]) <= ONE_HOUR_SECONDS) {
            entry->timestamps[new_count++] = entry->timestamps[i];
        }
    }
    entry->count = new_count;
    entry->timestamps[entry->count++] = now;

    int last_minute_count = count_recent_occurrences(entry, now, ONE_MINUTE_SECONDS);
    if (last_minute_count >= ONE_MINUTE_SECONDS) {
        entry->flood_mode = 1;
    }

    if (entry->flood_mode) {
        if (difftime(now, entry->last_print_time) >= ONE_HOUR_SECONDS) {
            printf("[FLOOD] %s\n", msg);
            entry->last_print_time = now;
        }
        return;
    }

    if (current_mode == LOG_MODE_FILTER) {
        int hour_count = count_recent_occurrences(entry, now, ONE_HOUR_SECONDS);
        if (hour_count > 1) {
            return; // 过滤重复日志
        }
    }

    printf("[LOG] %s\n", msg);
    entry->last_print_time = now;
}
