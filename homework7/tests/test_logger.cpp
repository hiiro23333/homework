#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

extern "C" {
    #include "../src/logger.h"
    #include "../src/time_utils.h"
}

// 模拟时间函数
static time_t mock_time = 0;
time_t current_time_mock() {
    return mock_time;
}

class LoggerTest : public ::testing::Test {
protected:
    const char* TEST_OUTPUT = "test_output.log";
    
    void SetUp() override {
        // 重定向stdout到测试文件
        freopen(TEST_OUTPUT, "w", stdout);
        
        // 初始化模拟时间
        mock_time = 0;
        set_current_time_function(current_time_mock);
        
        // 重置日志系统状态
        set_log_mode(LOG_MODE_NORMAL);
    }
    
    void TearDown() override {
        // 恢复stdout
        fclose(stdout);
        freopen("CON", "w", stdout); // Windows恢复控制台输出
        
        // 删除测试文件
        remove(TEST_OUTPUT);
    }
    
    std::vector<std::string> get_log_output() {
        std::ifstream log_file(TEST_OUTPUT);
        std::vector<std::string> lines;
        std::string line;
        
        while (std::getline(log_file, line)) {
            lines.push_back(line);
        }
        return lines;
    }
    
    int count_log_occurrences(const std::string& pattern) {
        auto logs = get_log_output();
        int count = 0;
        for (const auto& log : logs) {
            if (log.find(pattern) != std::string::npos) {
                count++;
            }
        }
        return count;
    }
    
    void advance_time(int seconds) {
        mock_time += seconds;
    }
};

// 测试普通模式下的日志输出
TEST_F(LoggerTest, NormalModeLogging) {
    log_message("Test message 1");
    log_message("Test message 2");
    log_message("Test message 1"); // 重复消息
    
    auto logs = get_log_output();
    ASSERT_EQ(logs.size(), 3);
    EXPECT_NE(logs[0].find("[LOG] Test message 1"), std::string::npos);
    EXPECT_NE(logs[1].find("[LOG] Test message 2"), std::string::npos);
    EXPECT_NE(logs[2].find("[LOG] Test message 1"), std::string::npos);
}

// 测试过滤模式下的重复日志过滤
TEST_F(LoggerTest, FilterModeOperation) {
    set_log_mode(LOG_MODE_FILTER);
    
    // 第一次出现 - 应该记录
    log_message("Filtered message");
    advance_time(1);
    
    // 10秒内重复 - 应该被过滤
    for (int i = 0; i < 5; i++) {
        log_message("Filtered message");
        advance_time(1);
    }
    
    // 超过1小时后再次出现 - 应该记录
    advance_time(3600);
    log_message("Filtered message");
    
    auto logs = get_log_output();
    ASSERT_EQ(logs.size(), 2);
    EXPECT_NE(logs[0].find("[LOG] Filtered message"), std::string::npos);
    EXPECT_NE(logs[1].find("[LOG] Filtered message"), std::string::npos);
}

// 测试洪水保护机制
TEST_F(LoggerTest, FloodProtection) {
    // 生成洪水日志 (超过60条/分钟)
    for (int i = 0; i < 65; i++) {
        log_message("Flood message");
        advance_time(1); // 每秒一条
    }
    
    // 验证洪水模式激活
    log_message("Flood message");
    auto logs = get_log_output();
    ASSERT_GE(logs.size(), 60);
    EXPECT_NE(logs.back().find("[FLOOD] Flood message"), std::string::npos);
    
    // 验证洪水模式下后续日志被抑制
    int flood_logs = count_log_occurrences("[FLOOD] Flood message");
    ASSERT_EQ(flood_logs, 1);
    
    // 1小时后应再次记录
    advance_time(3600);
    log_message("Flood message");
    
    logs = get_log_output();
    EXPECT_NE(logs.back().find("[FLOOD] Flood message"), std::string::npos);
}

// 测试时间戳管理
TEST_F(LoggerTest, TimestampManagement) {
    // 生成多条日志
    for (int i = 0; i < 10; i++) {
        log_message("Timing test");
        advance_time(60); // 每分钟一条
    }
    
    // 验证时间戳清理
    log_message("Timing test");
    auto logs = get_log_output();
    ASSERT_EQ(logs.size(), 11);
    
    // 验证没有意外进入洪水模式
    EXPECT_EQ(count_log_occurrences("[FLOOD]"), 0);
}

// 测试边界条件（最大日志条目）
TEST_F(LoggerTest, MaxLogEntries) {
    // 创建超过最大条目数的唯一日志
    for (int i = 0; i < 1030; i++) {
        char msg[50];
        snprintf(msg, sizeof(msg), "Unique message %d", i);
        log_message(msg);
    }
    
    auto logs = get_log_output();
    // 验证系统没有崩溃且处理了所有消息
    ASSERT_EQ(logs.size(), 1030);
    
    // 验证最后的消息被正确处理
    EXPECT_NE(logs.back().find("Unique message 1029"), std::string::npos);
}

// 测试混合模式切换
TEST_F(LoggerTest, ModeSwitching) {
    log_message("Before mode switch");
    
    set_log_mode(LOG_MODE_FILTER);
    log_message("Filtered message 1");
    log_message("Filtered message 1"); // 应被过滤
    
    set_log_mode(LOG_MODE_NORMAL);
    log_message("After mode switch");
    log_message("Filtered message 1"); // 应显示
    
    auto logs = get_log_output();
    ASSERT_EQ(logs.size(), 4);
    EXPECT_EQ(count_log_occurrences("Filtered message 1"), 2);
}

// 测试多线程安全
TEST_F(LoggerTest, ThreadSafety) {
    constexpr int THREAD_COUNT = 10;
    constexpr int MESSAGES_PER_THREAD = 100;
    
    auto worker = [](const char* msg) {
        for (int i = 0; i < MESSAGES_PER_THREAD; i++) {
            log_message(msg);
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    };
    
    std::vector<std::thread> threads;
    for (int i = 0; i < THREAD_COUNT; i++) {
        char msg[50];
        snprintf(msg, sizeof(msg), "Thread %d message", i);
        threads.emplace_back(worker, msg);
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    auto logs = get_log_output();
    ASSERT_EQ(logs.size(), THREAD_COUNT * MESSAGES_PER_THREAD);
    
    // 验证所有线程的消息都被记录
    for (int i = 0; i < THREAD_COUNT; i++) {
        char pattern[50];
        snprintf(pattern, sizeof(pattern), "Thread %d message", i);
        EXPECT_EQ(count_log_occurrences(pattern), MESSAGES_PER_THREAD);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}