TARGET = libstock.a
INCLUDE = -I. -Iinc
LDFLAGS =
FLAGS_OPTS = -O2 $(INCLUDE)
C_COMPILE = cc
C_FLAGS = $(FLAGS_OPTS)
CPP_COMPILE = c++
CPP_FLAGS = $(FLAGS_OPTS)
LINK = cc -o
LINK_OPTS = -L. -Llib $(LDFLAGS)
CONSOLE_LINK_OPTS = $(LINK_OPTS)
ORG_DIR =
ORG_LIB =
LOCAL_LIBS = $(ORG_LIB)
LIBS = $(LOCAL_LIBS)
AR = ar cr
RM = rm -rf
OBJS = stock.o

$(TARGET) : $(OBJS)
	$(AR) $(TARGET) $(OBJS)

$(OBJS) : %.o : %.cpp
	$(CPP_COMPILE) -c $(CPP_FLAGS) $< -o $@

clean :
	-$(RM) $(TARGET) $(OBJS)
