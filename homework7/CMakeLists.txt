cmake_minimum_required(VERSION 3.10)
project(LoggerSystem)

# 设置C标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# 添加 Google Test 子目录
add_subdirectory(third_party/googletest)

# 主程序构建
add_subdirectory(src)

# 测试构建
enable_testing()
add_subdirectory(tests)