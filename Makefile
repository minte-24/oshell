CC = gcc

CFLAGS = -Wall -Wextra -Werror

TARGET = oshell

SRC = src/main.c \
	src/parser.c \
	src/executor.c \
	src/builtins.c \
	src/path.c \
	src/utils.c \
	src/alias.c

OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
