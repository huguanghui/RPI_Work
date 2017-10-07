[TOC]

---
# GTest的使用
目标:
1.C/C++编程方法
2.makefile的编写
3.Linux命令操作
4.Gtest背景,作用，基础语法

## Step1 下载GTEST

## Step2 认识文件夹
    GTEST提供了对多个不同平台的支持，msvc文件夹用于微软的Visual Studio
                                 xcode文件夹用于Mac Xcode
                                 codegrear文件夹用于Borland C++ Builder
                                 make文件夹用于linux
## Step3 清除不需要的文件
    本环境用于linux平台，清理文件夹留下四个文件
    include      make      samples      src
## Step4 改写Makefile文件

```
GTEST_DIR = ..
USER_DIR = .
CPPFLAGS += -isystem $(GTEST_DIR)/include
CXXFLAGS += -g -Wall -Wextra -pthread
TESTS = run_test
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h
FILES = $(foreach d, $(USER_DIR), $(wildcard $(d)/*.cpp))
OBJS = $(patsubst %.cpp, %.o, $(FILES))

all : $(TESTS)

clean :
    rm -f $(TESTS) gtest_main.a *.o

.PHONY : clean

GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

gtest-all.o : $(GTEST_SRCS_)
    $(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
    $(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc

gtest_main.a :  gtest-all.o gtest_main.o
    $(AR) $(ARFLAGS) $@ $^

%.o : %.cpp
    $(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(TESTS) : $(OBJS) gtest_main.a
    $(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@
```
## Step5 添加自己的测试函数
### 1.0 sqrt.cpp
### 2.0 sqrt.h
### 3.0 sqrt_unittest.cpp
```
#include "sqrt.h"
#include "gtest/gtest.h"

TEST(SQRTest, Zero) {
    EXPECT_EQ(0, sqrt(0));
}
```

#  翻译
## Samples
如果你喜欢使用Gtest, 你应该看下一些Google Test样例代码.这个样例目录有一些如何使用一系列的Google Test属性.

- Sample#1显示了使用基础步骤Google Test去测试C++函数
- Sample#2显示了多成员函数的类的更加复杂的单元测试
- Sample#3使用了一个测试
- Sample#4使用Google Test的另一个基础测试
- Sample#5指导如何在多测试中复用测试
- Sample#6验证类型参数测试
- Sample#7指导参数值测试
- Sample#8在参数值测试中演示使用Combine()
- Sample#9
- Sample#10使用监测的API实现一个简单的内存栈检测