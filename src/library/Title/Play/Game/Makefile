# Makefile template for shared library

CC = g++ # C compiler
CFLAGS = -c -fPIC -Wall -Wextra  # C flags
LDFLAGS = -shared # linking flags
INCLUDES = -I../../../../../include
LIBS = -L ../ -lbmp -lGL -lGLU -lglut -lglui -lpthread
RM = rm -f # rm command
OBJDIR = ~/development/src/library #target directory
TARGET_LIB = libgame.so # target lib
TARGET_LIB2 = libgame3d.so # target lib
TARGET_LIB3 = libdrawdata.so # target lib
SRCS = Game.cpp # source files
SRCS2 = Game3d.cpp
SRCS3 = DrawData.cpp
OBJS = $(SRCS:.cpp=.o)
OBJS2 = $(SRCS2:.cpp=.o)
OBJS3 = $(SRCS3:.cpp=.o)

.PHONY: all
all:$(TARGET_LIB) $(TARGET_LIB2) $(TARGET_LIB3)
	cp $(TARGET_LIB) $(OBJDIR)
	cp $(TARGET_LIB2) $(OBJDIR)
	cp $(TARGET_LIB3) $(OBJDIR)	
$(TARGET_LIB): $(OBJS)
	$(CC) ${LDFLAGS} -o $@ $^

$(TARGET_LIB2): $(TARGET_LIB2) $(OBJS2) 	
	$(CC) -o $(TARGET_LIB2) $(OBJS2) -ldrawdata	

$(TARGET_LIB2): $(OBJS2) 
	$(CC) ${LDFLAGS} -o $@ $^ 

$(TARGET_LIB3): $(OBJS3)
	$(CC) ${LDFLAGS} -o $@ $^

$(OBJS): ${SRCS}
	$(CC) $(CFLAGS) $< $(LIBS) $(INCLUDES)

$(OBJS2): ${SRCS2}
	$(CC) $(CFLAGS) $< $(LIBS) $(INCLUDES)

$(OBJS3): ${SRCS3}
	$(CC) $(CFLAGS) $< $(LIBS) $(INCLUDES)

.PHONY: clean
clean:
	-${RM} ${TARGET_LIB} ${OBJS}
	-${RM} ${TARGET_LIB2} ${OBJS2}
	-${RM} ${TARGET_LIB3} ${OBJS3}
	cd $(OBJDIR); ${RM} ${TARGET_LIB}