#include <pthread.h>

int liczba_w;
int aktywne_watki;
pthread_mutex_t mutex;
pthread_cond_t cond_bariera;


void bariera_init(int liczba_watkow) {
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&cond_bariera, NULL);
  liczba_w = liczba_watkow;
  aktywne_watki = 0;
}

void bariera(void) {
  pthread_mutex_lock(&mutex);
  aktywne_watki++;
  if (aktywne_watki < liczba_w) {
    pthread_cond_wait(&cond_bariera, &mutex);
  } else {
    aktywne_watki = 0;
    pthread_cond_broadcast(&cond_bariera);
  }
  pthread_mutex_unlock(&mutex);
}