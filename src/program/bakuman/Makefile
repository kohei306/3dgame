# Makefile template for shared library

CC = g++ # C compiler
CFLAGS =    # C flags
INCLUDES = -I../../../include
LIBS = -lgame -lpause -lfailure -lclear -lfontdraw  -ltitle -lplay -lsetting -L../../library -lbmp -lGL -lGLU -lglut -lglui -lpthread 
RM = rm -f # rm command
OBJDIR = ~/development/src/program
SRCS = bakuman.cpp # source files
OBJS = $(SRCS:.cpp=.o)

.PHONY: all
all: ${OBJS}
	cp $(OBJS) $(OBJDIR)
	rm $(OBJS) 
$(OBJS): ${SRCS}
	$(CC) $< -o $@ $(LIBS) $(INCLUDES)  


.PHONY: clean
clean:
	-${RM} ${OBJS} 