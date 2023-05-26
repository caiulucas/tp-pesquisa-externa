all: main.o fileHandler.o sequencialIndexado.o
	@gcc main.o fileHandler.o sequencialIndexado.o -o exe
	@rm -r *.o
main.o: main.c
	@gcc main.c -c
fileHandler.o: fileHandler.c
	@gcc fileHandler.c -c
sequencialIndexado.o: sequencialIndexado.o
	@gcc sequencialIndexado.c -c
run:
	@./exe