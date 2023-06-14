all: main.o fileHandler.o indexed.o indexesTable.o b_tree.o
	@gcc main.o fileHandler.o indexed.o indexesTable.o b_tree.o -o exe
	@rm -r *.o
main.o: main.c
	@gcc main.c -c
indexed.o: indexed.c
	@gcc indexed.c -c
indexesTable.o: indexesTable.c
	@gcc indexesTable.c -c
fileHandler.o: fileHandler.c
	@gcc fileHandler.c -c
b_tree.o: b_tree.c
	@gcc b_tree.c -c
run:
	@./exe
