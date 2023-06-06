all: main.o fileHandler.o indexed.o indexesTable.o
	@gcc main.o fileHandler.o indexed.o indexesTable.o -o exe
	@rm -r *.o
main.o: main.c
	@gcc main.c -c
indexed.o: indexed.c
	@gcc indexed.c -c
indexesTable.o: indexesTable.c
	@gcc indexesTable.c -c
fileHandler.o: fileHandler.c
	@gcc fileHandler.c -c
run:
	@./exe