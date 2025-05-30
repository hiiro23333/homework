# 创建测试可执行文件
add_executable(logger_tests
    test_logger.cpp
)

# 链接库
target_link_libraries(logger_tests
    gtest_main
    gtest
    ${CMAKE_SOURCE_DIR}/src/logger.c
    ${CMAKE_SOURCE_DIR}/src/time_utils.c
)

# 添加测试
add_test(NAME LoggerTests COMMAND logger_tests)