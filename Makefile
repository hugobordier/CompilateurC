CC = gcc
CFLAGS = -Wall -g
TARGET = compilateur
SRCDIR = src
INCDIR = include
OBJDIR = obj

# Liste des fichiers source
SRCS = $(wildcard $(SRCDIR)/*.c)
# Générer les noms des fichiers objet
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Cible principale
$(TARGET): $(OBJS)
    $(CC) $(CFLAGS) -o $@ $^

# Règle pour compiler chaque fichier source en fichiers objet
$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
    $(CC) $(CFLAGS) -c $< -o $@ -I$(INCDIR)

.PHONY: clean
clean:
    rm -f $(OBJS) $(TARGET)
