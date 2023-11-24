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
zad2: zad2.o 
	$(LOADER) $(OPT) zad2.o -o zad2

# jak uzyskac plik moj_program.o ?
zad2.o: zad2.c
	$(CCOMP) -c $(OPT) zad2.c