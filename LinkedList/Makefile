# 定义编译器
CXX = g++
# 定义编译选项
CXXFLAGS = -Wall -g
# 定义头文件路径
INCLUDES = -I.

# 目标文件
all: main.exe clean

# 编译生成main.exe
main.exe: main.o
	$(CXX) $(CXXFLAGS) -o main.exe main.o

# 编译main.cpp
main.o: main.cpp LinkedList.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c main.cpp

# 清理编译生成的文件 (适用于 Windows)
clean:
	del /Q main.o
