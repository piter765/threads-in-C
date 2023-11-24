#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include <unistd.h>

int zmienna_wspolna=0;

#define WYMIAR 1000
#define ROZMIAR WYMIAR*WYMIAR
#define THREADS_NUMBER 10

void* f_watku(void* arg) {
  int system_ID = pthread_self();
  int thread_ID = *((int*)arg);
  printf("system ID: %d, przeslane ID: %d \n", system_ID, thread_ID);

  return (NULL);
 }


int main() {
	
  pthread_t tid[THREADS_NUMBER] = {0}; 
  int thread_identifiers[THREADS_NUMBER] = {0};

	for(int i = 0; i < THREADS_NUMBER; i++){
    thread_identifiers[i] = i;
    pthread_create(&tid[i], NULL, f_watku, &i);
  }  

  for(int i = 0; i < THREADS_NUMBER; i++){
    pthread_join(tid[i], NULL);
  }
}

