CC = gcc -fopenmp

LD = gcc -fopenmp

OPT = -O3

INC = 

LIB = -pthread

openmp_petle: openmp_petle.o
	$(LD) $(OPT) -o openmp_petle openmp_petle.o 

openmp_petle.o: openmp_petle.c
	$(CC) -c $(OPT) openmp_petle.c $(INC)

clean:
	rm -f *.o openmp_petle
