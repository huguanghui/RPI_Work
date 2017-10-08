TARGET = run_test
USER_DIR = .
INCLUDE = -I. -Iinc
LDFLAGS = 
FLAGS_OPTS = -O2 $(INCLUDE)
C_COMPILE = cc
C_FLAGS = $(FLAGS_OPTS)
CPP_COMPILE = c++
CPP_FLAGS = $(FLAGS_OPTS)
LINK = c++ -o
LINK_OPTS = -L. -Llib $(LDFLAGS)
CONSOLE_LINK_OPTS = $(LINK_OPTS)
ORG_DIR = ./lib
ORG_LIB = $(foreach d, $(ORG_DIR), $(wildcard $(d)/*.a))
LOCAL_LIBS = $(ORG_LIB)
LIBS = $(LOCAL_LIBS)
AR = ar cr
RM = rm -rf
FILES = $(foreach d, $(USER_DIR), $(wildcard $(d)/*.cpp))
OBJS = $(patsubst %.cpp, %.o, $(FILES))

str_main : str_main.o
	$(LINK) $@ $< $(CONSOLE_LINK_OPTS) $(LIBS)

hangman : hangman.o
	$(LINK) $@ $< $(CONSOLE_LINK_OPTS) $(LIBS)

$(OBJS) : %.o : %.cpp
	$(CPP_COMPILE) -c $(CPP_FLAGS) $< -o $@

clean :
	-$(RM) $(TARGET) $(OBJS) str_main hangmain
