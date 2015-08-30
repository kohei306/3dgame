# Makefile template for shared library

CC = g++ # C compiler
CFLAGS = -c -fPIC -Wall -Wextra  # C flags
LDFLAGS = -shared # linking flags
RM = rm -f # rm command
OBJDIR = ~/development/src/library #target directory
TARGET_LIB = libbmp.so # target lib
SRCS = bmp.cpp # source files
OBJS = $(SRCS:.cpp=.o)

.PHONY: all
all: ${TARGET_LIB}
	cp $(TARGET_LIB) $(OBJDIR)

$(TARGET_LIB): $(OBJS)
	$(CC) ${LDFLAGS} -o $@ $^

$(OBJS): ${SRCS}
	$(CC) $(CFLAGS) $< 


.PHONY: clean
clean:
	-${RM} ${TARGET_LIB} ${OBJS} $(SRCS:.cpp=.o)
	cd $(OBJDIR); ${RM} ${TARGET_LIB}