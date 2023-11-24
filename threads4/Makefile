# kompilator c
CCOMP = gcc

# konsolidator
LOADER = gcc

# opcje optymalizacji:
# wersja do debugowania
#OPT = -g -DDEBUG
OPT = -O0 -g
# wersja zoptymalizowana do mierzenia czasu
# OPT = -O3

# pliki naglowkowe
#INC = -I../pomiar_czasu

# biblioteki
#LIB = -L../pomiar_czasu -lm

# zaleznosci i komendy
pub_sym_1: pub_sym_1.o 
	$(LOADER) $(OPT) pub_sym_1.o -o pub_sym_1

# jak uzyskac plik moj_program.o ?
pub_sym_1.o: pub_sym_1.c
	$(CCOMP) -c $(OPT) pub_sym_1.c

pub_sym_1_2: pub_sym_1_2.o 
	$(LOADER) $(OPT) pub_sym_1_2.o -o pub_sym_1_2

# jak uzyskac plik moj_program.o ?
pub_sym_1_2.o: pub_sym_1_2.c
	$(CCOMP) -c $(OPT) pub_sym_1_2.c

clean:
	rm -f *.o pub_sym_1 pub_sym_1_2
