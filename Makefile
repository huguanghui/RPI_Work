TARGET = onvif_server
INCLUDE = -I. -Iinc
LDFLAGS = -pthread -lonvif_org
FLAGS_OPTS = -O2 -DWITH_DOM $(INCLUDE)
C_COMPILE = cc
C_FLAGS = $(FLAGS_OPTS)
CPP_COMPILE = c++
CPP_FLAGS = $(FLAGS_OPTS)
LINK = cc -o
LINK_OPTS = -L. -Llib $(LDFLAGS)
CONSOLE_LINK_OPTS = $(LINK_OPTS)
ORG_DIR = ./lib
ORG_LIB = $(ORG_DIR)/libonvif_org.a
LOCAL_LIBS = $(ORG_LIB)
LIBS = $(LOCAL_LIBS)
AR = ar cr
RM = rm -rf
OBJS = src/ovf_main.o src/ovf_tds.o src/ovf_tr2.o src/ovf_funs.o src/ovf_ds.o src/wsaapi.o src/wsddapi.o

$(TARGET) : $(OBJS)
	$(LINK) $(TARGET) $(OBJS) $(CONSOLE_LINK_OPTS) $(LIBS)

$(OBJS) : %.o : %.c
	$(C_COMPILE) -c $(C_FLAGS) $< -o $@

clean :
	-$(RM) $(TARGET) $(OBJS)
