main: main.o calculo.o matrix.o simulacao.o
	gcc main.o calculo.o matrix.o simulacao.o -lm -o main

matrix.o: matrix.c matrix.h
	gcc -c matrix.c -o matrix.o

calculo.o: calculo.c calculo.h matrix.h 
	gcc -c calculo.c -o calculo.o

simulacao.o: simulacao.c simulacao.h matrix.h calculo.h
	gcc -c simulacao.c -o simulacao.o

main.o: main.c calculo.h matrix.h simulacao.h
	gcc -c main.c -o main.o

clean:
	rm main *.o