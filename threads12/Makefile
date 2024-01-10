# kompilator c
CCOMP = /usr/bin/mpicc

# konsolidator
LOADER = /usr/bin/mpicc

# program uruchomieniowy MPI
MPI_run = /usr/bin/mpiexec 

# opcje optymalizacji:
# wersja do debugowania
OPT = -g -DDEBUG
# wersja zoptymalizowana do mierzenia czasu
# OPT = -O3
# OPT = -O2 -fopenmp

# pliki naglowkowe
#INC = -I../pomiar_czasu

# biblioteki
#LIB = -L../pomiar_czasu -lm
LIB = -lm

all: oblicz_PI run 

run: oblicz_PI
	$(MPI_run) -np 4 ./oblicz_PI

# zaleznosci i komendy
oblicz_PI : oblicz_PI.o
	$(LOADER) $(OPT) oblicz_PI.o -o oblicz_PI $(LIB)

# jak uzyskac plik moj_program.o ?
oblicz_PI.o: oblicz_PI.c 
	$(CCOMP) -c $(OPT) oblicz_PI.c

clean:
	rm -f *.o oblicz_PI
