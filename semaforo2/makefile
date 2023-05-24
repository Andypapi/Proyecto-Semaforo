# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Wpedantic

# Source files
SRCS = main.c graph.c traffic_lights.c user_interface.c

# Object files
OBJS = $(SRCS:.c=.o)

# Binary
TARGET = program_output

# Default target
all: $(TARGET)

# Compile source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files into binary
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Clean
clean:
	rm -f $(OBJS) $(TARGET)
