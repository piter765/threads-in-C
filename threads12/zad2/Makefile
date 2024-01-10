# kompilator c
CCOMP = /usr/bin/mpicc

# konsolidator
LOADER = /usr/bin/mpicc

# program uruchomieniowy MPI
MPI_run = /usr/bin/mpiexec 

# opcje optymalizacji:
# wersja do debugowania
#OPT = -g -DDEBUG
# wersja zoptymalizowana do mierzenia czasu
# OPT = -O3
OPT = -O2 -fopenmp

# pliki naglowkowe
#INC = -I../pomiar_czasu

# biblioteki
#LIB = -L../pomiar_czasu -lm
LIB = -lm

all: mat_vec_row_MPI run 

run: mat_vec_row_MPI
	$(MPI_run) -np 4 ./mat_vec_row_MPI

# zaleznosci i komendy
mat_vec_row_MPI : mat_vec_row_MPI.o
	$(LOADER) $(OPT) mat_vec_row_MPI.o -o mat_vec_row_MPI $(LIB)

# jak uzyskac plik moj_program.o ?
mat_vec_row_MPI.o: mat_vec_row_MPI.c 
	$(CCOMP) -c $(OPT) mat_vec_row_MPI.c

clean:
	rm -f *.o mat_vec_row_MPI
