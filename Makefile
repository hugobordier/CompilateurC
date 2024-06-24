CC = gcc
CFLAGS = -Wall -g
TARGET = compilateur
SRCDIR = src
INCDIR = include
OBJDIR = obj

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $

$(OBJS):$(OBJDIR)/%.o:$(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCDIR)

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)
