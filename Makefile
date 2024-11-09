main: main.o calculo.o matrix.o integral.o simulacao.o
	gcc main.o calculo.o matrix.o integral.o simulacao.o -lm -o main

matrix.o: matrix.c matrix.h
	gcc -c matrix.c -o matrix.o

integral.o: integral.c integral.h
	gcc -c integral.c -o integral.o

calculo.o: calculo.c calculo.h matrix.h integral.h
	gcc -c calculo.c -o calculo.o

simulacao.o: simulation.c simulation.h matrix.h calculate.h
	gcc -c simulation.c -o simulation.o

main.o: main.c calculo.h matrix.h integral.h simulacao.h
	gcc -c main.c -o main.o

clean:
	rm main *.o