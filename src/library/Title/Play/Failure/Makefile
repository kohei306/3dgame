# Makefile template for shared library

CC = g++ # C compiler
CFLAGS = -c -fPIC -Wall -Wextra  # C flags
LDFLAGS = -shared # linking flags
INCLUDES = -I../../../../../include
LIBS = -L ../ -lbmp -lGL -lGLU -lglut
RM = rm -f # rm command
OBJDIR = ~/development/src/library #target directory
TARGET_LIB = libfailure.so # target lib
SRCS = Failure.cpp # source files
OBJS = $(SRCS:.cpp=.o)

.PHONY: all
all:$(TARGET_LIB)
	cp $(TARGET_LIB) $(OBJDIR)
$(TARGET_LIB): $(OBJS)
	$(CC) ${LDFLAGS} -o $@ $^

$(OBJS): ${SRCS}
	$(CC) $(CFLAGS) $< $(LIBS) $(INCLUDES)


.PHONY: clean
clean:
	-${RM} ${TARGET_LIB} ${OBJS}
	cd $(OBJDIR); ${RM} ${TARGET_LIB}