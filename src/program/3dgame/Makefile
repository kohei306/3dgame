# Makefile template for shared library

CC = g++ # C compiler
CFLAGS =    # C flags
INCLUDES = -I../../../include
LIBS =  -L../../library -lbmp -lGL -lGLU -lglut -lglui -lpthread -lgame3d -ldrawdata 
RM = rm -f # rm command
OBJDIR = ~/development/src/program
SRCS = 3dgame.cpp # source files
OBJS = $(SRCS:.cpp=.o)

.PHONY: all
all: ${OBJS}
	cp $(OBJS) $(OBJDIR)
	# rm $(OBJS) 
$(OBJS): ${SRCS}
	$(CC) $< -o $@ $(LIBS) $(INCLUDES)  


.PHONY: clean
clean:
	-${RM} ${OBJS} 