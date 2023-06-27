CC := gcc
CFLAGS := -c -Wall

SRC := main.c indexed.c file_handler.c b_tree.c utils.c binary_tree.c b_star.c
OBJ := $(SRC:.c=.o)
EXECUTABLE := exe

.PHONY: all clean run

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $^ -o $@
	@rm -r $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

run: $(EXECUTABLE)
	@./$(EXECUTABLE)

clean:
	rm -rf $(OBJ) $(EXECUTABLE)