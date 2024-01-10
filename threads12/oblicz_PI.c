#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "mpi.h"

#define SCALAR double
//#define SCALAR float

#ifndef M_PI // standardy C99 i C11 nie wymagajÄ definiowania staĹej M_PI
#define M_PI (3.14159265358979323846)
#endif

int main(int argc, char** argv) { // program obliczania przybliĹźenia PI za pomocÄ wzoru Leibniza
                  // PI = 4 * ( 1 - 1/3 + 1/5 - 1/7 + 1/9 - 1/11 + itd. )
  int max_liczba_wyrazow=0;
  int rank, size, n;
  double suma_final = 0.0;

  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank ); 
  MPI_Comm_size( MPI_COMM_WORLD, &size ); 

  // printf("Podaj maksymalna liczba wyrazow do obliczenia przyblizenia PI\n");
  // scanf("%d", &max_liczba_wyrazow);

  if (rank == 0) { max_liczba_wyrazow = 1000; }
  MPI_Bcast(&max_liczba_wyrazow, 1, MPI_INT, 0, MPI_COMM_WORLD);
  //  double t = MPI_Wtime();
 // wzĂłr: PI/4 = 1 - 1/3 + 1/5 - 1/7 + 1/9 itd. itp.  
  SCALAR suma_plus=0.0;
  SCALAR suma_minus=0.0;
  int i=0;

  int start, end;

  n = ceil( max_liczba_wyrazow / size);
  start = n * rank;
  if(rank == size - 1){ end = max_liczba_wyrazow;}
  else { end = start + n;}
  printf("Proces o nr %d ma zakres od %d do %d\n", rank, start, end);

  for(i=start; i<end; i++){ 
    int j = 1 + 4*i; 
    suma_plus += 1.0/j;
    suma_minus += 1.0/(j+2.0);
    //printf("PI obliczone: %20.15lf, aktualna poprawka: %20.15lf\n",
    //  	 4*(suma_plus-suma_minus), 4.0/j-4.0/(j+2.0));
  }
  double pi_approx = 4*(suma_plus-suma_minus);

  MPI_Reduce(&pi_approx, &suma_final, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

  //  t = MPI_Wtime() - t;
  
  if (rank == 0) {
  printf("PI obliczone: \t\t\t%20.15lf\n", suma_final);
  printf("PI z biblioteki matematycznej: \t%20.15lf\n", M_PI);
  //  printf("Czas obliczeĹ: %lf\n", t);
  }
  
}

