# Define variables
CC = gcc                  # The compiler to use
CFLAGS = -Wall -Wextra -std=c99  # Compilation options
SRCDIR = src              # Directory for source files
OBJDIR = obj              # Directory for object files
BINDIR = bin              # Directory for binary files
TARGET = $(BINDIR)/compilateur  # Name of the generated executable

# List of source files
SOURCES = $(wildcard $(SRCDIR)/*.c)
# Convert source files to object files
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))

# Default rule: compile the executable
$(TARGET): $(OBJECTS)
    @mkdir -p $(BINDIR)   # Create the binary directory if it doesn't exist
    $(CC) $(CFLAGS) -o $@ $^  # Compile the object files into an executable
    @echo "Compilation finished: $@"

# Rule to compile source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
    @mkdir -p $(OBJDIR)   # Create the object directory if it doesn't exist
    $(CC) $(CFLAGS) -c -o $@ $<  # Compile a source file into an object file
    @echo "Compiled: $< -> $@"

# Rule to clean up generated files
clean:
    @rm -rf $(OBJDIR) $(BINDIR)  # Remove the object and binary directories
    @echo "Cleanup finished."

# Directive to indicate that clean is not a file
.PHONY: clean
