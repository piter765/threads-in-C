#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define WYMIAR 18

int main ()
{
  double a[WYMIAR];

#pragma omp  parallel for default(none) shared(a)
  for(int i=0;i<WYMIAR;i++) a[i]=1.02*i;

  // petla sekwencyjna
  double suma=0.0;
  for(int i=0;i<WYMIAR;i++) {
      suma += a[i];
  }
  
  printf("Suma wyrazow tablicy: %lf\n", suma);

  // petla do modyfikacji - docelowo rownolegla w OpenMP
  double suma_parallel=0.0;
  #pragma omp parallel for ordered schedule(dynamic) default(none) shared (suma_parallel, a) num_threads(4)

  for(int i=0;i<WYMIAR;i++) {
    int id_w = omp_get_thread_num();
    #pragma omp critical
    suma_parallel += a[i];
    #pragma omp ordered
    printf("a[%2d]->W_%1d  \n",i,id_w); 
  }

  printf("\nSuma wyrazow tablicy rownolegle (z klauzula - ....: %lf\n",
	 suma_parallel);

}