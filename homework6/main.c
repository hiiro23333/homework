#include <stdio.h>
#include <unistd.h> // for sleep/usleep
#include "logger.h"

int main() {
    // ========= 第一阶段：普通打印 =========
    printf("===== 测试阶段 1：普通模式打印 =====\n");
    set_log_mode(LOG_MODE_NORMAL);

    log_message("Function A executed.");
    sleep(1);
    log_message("Function A executed.");
    sleep(1);
    log_message("Function B executed.");
    sleep(2);

    // ========= 第二阶段：过滤打印 =========
    printf("\n===== 测试阶段 2：过滤模式打印（1小时内同样内容仅打印一次） =====\n");
    set_log_mode(LOG_MODE_FILTER);

    log_message("Filtered log - only once");
    sleep(1);
    log_message("Filtered log - only once");
    sleep(1);
    log_message("Filtered log - only once");
    sleep(2);

    // ========= 第三阶段：海量日志屏蔽 =========
    printf("\n===== 测试阶段 3：模拟海量日志（>=60条/分钟） =====\n");
    set_log_mode(LOG_MODE_NORMAL); // 模式不影响屏蔽逻辑

    for (int i = 0; i < 65; ++i) {
        log_message("Flooding Log Message!");
        usleep(100000); // 0.1秒间隔，6.5秒内输出65次
    }

    printf("\n===== 检查海量日志屏蔽是否生效（应不再打印） =====\n");
    log_message("Flooding Log Message!");
    sleep(1);
    log_message("Flooding Log Message!");
    sleep(1);

    // 非海量日志应能正常打印
    printf("\n===== 打印其他正常日志（应能打印） =====\n");
    log_message("Function C executed.");
    sleep(1);
    log_message("Function C executed.");

    return 0;
}
