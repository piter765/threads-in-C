#include<stdio.h>
#include<pthread.h>
#include<math.h>

double funkcja ( double x );

double calka_zrownoleglenie_petli(double a, double b, double dx, int l_w);

static int l_w_global=0;

static double calka_global=0.0;
static double a_global;
static double b_global;
static double dx_global;
static int N_global;

void* calka_fragment_petli_w(void* arg_wsk);

pthread_mutex_t muteks;

double calka_zrownoleglenie_petli(double a, double b, double dx, int l_w){

  int N = ceil((b-a)/dx);
  double dx_adjust = (b-a)/N;

  printf("Obliczona liczba trapezów: N = %d, dx_adjust = %lf\n", N, dx_adjust);
  //printf("a %lf, b %lf, n %d, dx %.12lf (dx_adjust %.12lf)\n", a, b, N, dx, dx_adjust);


  N_global = N;
  a_global = a;
  b_global = b;
  dx_global = dx;
  l_w_global = l_w;

  // tworzenie struktur danych do obsługi wielowątkowości

  int i = 0;
  int thread_ID[l_w];
  pthread_mutex_init(&muteks, NULL);
  pthread_t watki[l_w];


  // tworzenie wątków
  for(i = 0; i < l_w; i++){
    thread_ID[i] = i;
    pthread_create(&watki[i], NULL, calka_fragment_petli_w, 
    &thread_ID[i]); 
  }


  // oczekiwanie na zakończenie pracy wątków
  for( i= 0; i < l_w; i++){
    pthread_join(watki[i], NULL); 
  }

  return(calka_global);
}

void* calka_fragment_petli_w(void* arg_wsk){

  int my_id;

  double a, b, dx; // skąd pobrać dane a, b, dx, N, l_w ? 
  int N, l_w;      // wariant 1 - globalne

  my_id = *( (int *) arg_wsk ); 
  a = a_global; // itd. itp. - wartości globalne nadaje calka_zrownoleglenie_petli
  b = b_global;
  dx = dx_global;
  N = N_global;
  l_w = l_w_global;

  // dekompozycja cykliczna
  // int my_start = my_id;
  // int my_end = N;
  // int my_stride = l_w;

  // dekompozycja blokowa
  int el_na_watek = ceil( (float) N / l_w );
  int my_start = el_na_watek*my_id;
  int my_end = el_na_watek*(my_id+1);
  int my_stride = 1;

  // something else ? (dekompozycja blokowo-cykliczna)

  printf("\nWątek %d: my_start %d, my_end %d, my_stride %d\n", 
	 my_id, my_start, my_end, my_stride);


  int i;
  double calka = 0.0;
  for(i=my_start; i<my_end; i+=my_stride){

    double x1 = a + i*dx;
    calka += 0.5*dx*(funkcja(x1)+funkcja(x1+dx));
    //printf("i %d, x1 %lf, funkcja(x1) %lf, całka = %.15lf\n", 
    //	   i, x1, funkcja(x1), calka);
  }

  pthread_mutex_lock(&muteks);
  calka_global += calka;
  pthread_mutex_unlock(&muteks);

}
