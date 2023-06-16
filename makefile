all: main.o fileHandler.o indexed.o indexesTable.o btree.o
	@gcc main.o fileHandler.o indexed.o indexesTable.o btree.o -o exe -Wall
	@rm -r *.o
main.o: main.c
	@gcc main.c -c
indexed.o: indexed.c
	@gcc indexed.c -c
indexesTable.o: indexesTable.c
	@gcc indexesTable.c -c
fileHandler.o: fileHandler.c
	@gcc fileHandler.c -c
btree.o: btree.c
	@gcc btree.c -c
run:
	@./exe
