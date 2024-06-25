# Compilateur
CC = gcc
CFLAGS = -Wall -g
LDFLAGS =

# Répertoires
SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include

# Cibles
TARGET = compilateur
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Règles
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCLUDE_DIR)

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)
