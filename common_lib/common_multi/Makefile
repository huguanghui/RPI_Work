TARGET = test_multi
INCLUDE = -I. -Iinc
LDFLAGS = -pthread
FLAGS_OPTS = -O2 $(INCLUDE)
C_COMPILE = cc
C_FLAGS = $(FLAGS_OPTS)
CPP_COMPILE = c++
CPP_FLAGS = $(FLAGS_OPTS)
LINK = c++ -o
LINK_OPTS = -L. -Llib $(LDFLAGS)
CONSOLE_LINK_OPTS = $(LINK_OPTS)
ORG_DIR = ./lib
ORG_LIB =
LOCAL_LIBS = $(ORG_LIB)
LIBS = $(LOCAL_LIBS)
AR = ar cr
RM = rm -rf
OBJS = common_multi.o common_main.o

$(TARGET) : $(OBJS)
	$(LINK) $(TARGET) $(OBJS) $(CONSOLE_LINK_OPTS) $(LIBS)

$(OBJS) : %.o : %.cpp
	$(CPP_COMPILE) -c $(CPP_FLAGS) $< -o $@

clean :
	-$(RM) $(TARGET) $(OBJS)
