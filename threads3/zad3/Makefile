# kompilator c
CCOMP = gcc

# konsolidator
LOADER = gcc

# opcje optymalizacji:
# wersja do debugowania
OPT = -g -DDEBUG
# wersja zoptymalizowana do mierzenia czasu
# OPT = -O3

# pliki naglowkowe
#INC = -I../pomiar_czasu

# biblioteki
#LIB = -L../pomiar_czasu -lm

# zaleznosci i komendy
zad3: zad3.o 
	$(LOADER) $(OPT) zad3.o -o zad3

# jak uzyskac plik moj_program.o ?
zad3.o: zad3.c
	$(CCOMP) -c $(OPT) zad3.c