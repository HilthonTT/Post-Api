# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra

# Executable name
TARGET = socket

# Source, build, and include directories
SRCDIR = src
OBJDIR = build
INCDIR = include

# Source files and object files
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Include directory
INCLUDES = -I$(INCDIR)

# Libraries to link against
LIBS = -lws2_32

# Default rule to build executable
$(OBJDIR)/$(TARGET): $(OBJS)
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJS) $(LIBS)

# Rule to compile source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Rule to clean up the build
clean:
	rm -f $(OBJDIR)/*.o $(OBJDIR)/$(TARGET)
	rmdir $(OBJDIR)

# Phony targets (not actual files)
.PHONY: clean
