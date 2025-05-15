# 编译器
CC = gcc

# 编译选项（-Wall 显示警告，-g 开启调试信息）
CFLAGS = -Wall -g

# 项目文件
SRCS = main.c logger.c
OBJS = $(SRCS:.c=.o)
TARGET = logtest

# 默认目标
all: $(TARGET)

# 链接目标程序
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# 运行程序
run: $(TARGET)
	./$(TARGET)

# 清理编译生成的文件
clean:
	rm -f $(OBJS) $(TARGET)
