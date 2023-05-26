all: main.o fileHandler.o
	@gcc main.o fileHandler.o -o exe
	@rm -r *.o
main.o: main.c
	@gcc main.c -c
fileHandler.o: fileHandler.c
	@gcc fileHandler.c -c
run:
	@./exe