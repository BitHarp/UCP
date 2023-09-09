# Compiler and compiler flags
CC = gcc
CFLAGS = -Wall -ansi -pedantic

# Executable name
TARGET = life

# Source and header files
SRCS = life.c random.c
HEADERS = random.h

# Object files
OBJS = $(SRCS:.c=.o)

# Build target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile source files to object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

# Clean the build files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony target to prevent conflicts with files of the same name
.PHONY: clean