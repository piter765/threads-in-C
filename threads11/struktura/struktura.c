#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "mpi.h"
#include <string.h>

struct S {
  char imie[10];
  int liczba_int;
  double liczba_double;
};

int main(int argc, char** argv) {
  
  int rank, size, source, dest, tag, i, rozmiar_pakietu, rozmiar, pozycja, prev; 
  void* bufor;
  struct S s;

  strcpy(s.imie, "Piotr");
  s.liczba_int = 0;
  s.liczba_double = 0.0;

  MPI_Status status;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  MPI_Pack_size(10, MPI_CHAR, MPI_COMM_WORLD, &rozmiar);
  rozmiar_pakietu = rozmiar;
  MPI_Pack_size(1, MPI_INT, MPI_COMM_WORLD, &rozmiar);
  rozmiar_pakietu += rozmiar;
  MPI_Pack_size(1, MPI_DOUBLE, MPI_COMM_WORLD, &rozmiar);
  rozmiar_pakietu += rozmiar;

  bufor = (void *)malloc(rozmiar_pakietu);
  
  if(size > 1) {
    
    if(rank == 0) {
      dest = 1; tag = 0;
      strcpy(s.imie, "Piotr");
      s.liczba_int += 5;
      s.liczba_double += 3.3;
      MPI_Pack(&s.imie, 10, MPI_CHAR, bufor, rozmiar_pakietu, &pozycja, MPI_COMM_WORLD);
      MPI_Pack(&s.liczba_int, 1, MPI_INT, bufor, rozmiar_pakietu, &pozycja, MPI_COMM_WORLD);
      MPI_Pack(&s.liczba_double, 1, MPI_DOUBLE, bufor, rozmiar_pakietu, &pozycja, MPI_COMM_WORLD);
      MPI_Send(bufor, pozycja, MPI_PACKED, dest, tag, MPI_COMM_WORLD );
      printf("\nProces %d wyslal do %d, imie %s, liczbe_int = %d, liczbe_double = %lf\n",
       rank, dest, s.imie, s.liczba_int, s.liczba_double );
    }
    if (rank < size - 1 && rank != 0) {
      prev = rank - 1;
      dest = rank + 1;
      MPI_Recv(bufor, rozmiar_pakietu, MPI_PACKED, prev, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
      pozycja = 0;
      MPI_Unpack(bufor, rozmiar_pakietu, &pozycja, &s.imie, 10, MPI_CHAR, MPI_COMM_WORLD);
      MPI_Unpack(bufor, rozmiar_pakietu, &pozycja, &s.liczba_int, 1, MPI_INT, MPI_COMM_WORLD);
      MPI_Unpack(bufor, rozmiar_pakietu, &pozycja, &s.liczba_double, 1, MPI_DOUBLE, MPI_COMM_WORLD);
      printf("\nProces %d odebral od %d, imie %s, liczbe_int = %d, liczbe_double = %lf\n",
       rank, status.MPI_SOURCE, s.imie, s.liczba_int, s.liczba_double );

      pozycja = 0;
      strcpy(s.imie,"Piotr");
      s.liczba_int += 5;
      s.liczba_double += 3.3;
      MPI_Pack(&s.imie, 10, MPI_CHAR, bufor, rozmiar_pakietu, &pozycja, MPI_COMM_WORLD);
      MPI_Pack(&s.liczba_int, 1, MPI_INT, bufor, rozmiar_pakietu, &pozycja, MPI_COMM_WORLD);
      MPI_Pack(&s.liczba_double, 1, MPI_DOUBLE, bufor, rozmiar_pakietu, &pozycja, MPI_COMM_WORLD);
      MPI_Send(bufor, pozycja, MPI_PACKED, dest, tag, MPI_COMM_WORLD ); 
      printf("\nProces %d wyslal do %d, imie %s, liczbe_int = %d, liczbe_double = %lf\n",
       rank, dest, s.imie, s.liczba_int, s.liczba_double );
    }
  }
  else {
    printf("Pojedynczy proces o randze: %d (brak komunikatów)\n", rank);
  }

  MPI_Finalize(); 
  free(bufor);
  return(0);
}
