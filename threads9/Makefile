CC = gcc -fopenmp

LD = gcc -fopenmp

OPT = -O3

INC = 

LIB = -pthread

openmp_petle_simple: openmp_petle_simple.o
	$(LD) $(OPT) -o openmp_petle_simple openmp_petle_simple.o 

openmp_petle_simple.o: openmp_petle_simple.c
	$(CC) -c $(OPT) openmp_petle_simple.c $(INC)

clean:
	rm -f *.o openmp_petle_simple
