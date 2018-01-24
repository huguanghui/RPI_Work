TARGET = gsoap_log
INCLUDE = -I. -Iinc
LDFLAGS = -pthread
FLAGS_OPTS = -O2  $(INCLUDE)
C_COMPILE = cc
C_FLAGS = $(FLAGS_OPTS)
CPP_COMPILE = c++
CPP_FLAGS = $(FLAGS_OPTS)
LINK = cc -o
LINK_OPTS = -L. -Llib $(LDFLAGS)
CONSOLE_LINK_OPTS = $(LINK_OPTS)
ORG_DIR = ./lib
ORG_LIB = 
LOCAL_LIBS = $(ORG_LIB)
LIBS = $(LOCAL_LIBS)
AR = ar cr
RM = rm -rf
OBJS = gsoap_log_api.o gsoap_log_main.o

$(TARGET) : $(OBJS)
	$(LINK) $(TARGET) $(OBJS) $(CONSOLE_LINK_OPTS) $(LIBS)

$(OBJS) : %.o : %.c
	$(C_COMPILE) -c $(C_FLAGS) $< -o $@

clean :
	-$(RM) $(TARGET) $(OBJS)
