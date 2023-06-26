CC := gcc
CFLAGS := -c -Wall

SRC := main.c indexed.c fileHandler.c b_tree.c b_star_tree.c utils.c binary_tree.c
OBJ := $(SRC:.c=.o)
EXECUTABLE := exe

DIR_NAME = data

.PHONY: all clean run

all: $(EXECUTABLE)
all: create_directory

$(EXECUTABLE): $(OBJ)
	$(CC) $^ -o $@
	@rm -r $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

run: $(EXECUTABLE)
	@./$(EXECUTABLE)

create_directory:
	mkdir $(DIR_NAME)

clean:
	rm -rf $(OBJ) $(EXECUTABLE)
