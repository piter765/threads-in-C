#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
struct struct_t { int a; double b; char c; };
void * zadanie_watku (void * arg_wsk);
int main() {
  pthread_t tid; pthread_t tid2;
  struct struct_t struktura_main = { 2, 5.6, 'a' };
  pthread_create(&tid, NULL, zadanie_watku, &struktura_main);
  pthread_create(&tid2, NULL, zadanie_watku, &struktura_main);
  pthread_join( tid, NULL);
  pthread_join( tid2, NULL);

  printf("Dostep do wartosci w MAIN: a = %d, b = %lf, c = %c\n", struktura_main.a, struktura_main.b, struktura_main.c);
}

void * zadanie_watku (void * arg_wsk){

  struct struct_t *wskaznik_do_struktury_main = arg_wsk;
  struct struct_t struktura_lokalna;

  struktura_lokalna = *( (struct struct_t *) arg_wsk );

  struktura_lokalna.a += 1;
  struktura_lokalna.b += 1;
  struktura_lokalna.c += 1;

  wskaznik_do_struktury_main->a += 1;
  wskaznik_do_struktury_main->b += 1;
  wskaznik_do_struktury_main->c += 1;

  printf("Dostep do wartosci z procedury main: a = %d, b = %lf, c = %c\n",
  wskaznik_do_struktury_main->a, wskaznik_do_struktury_main->b,
  wskaznik_do_struktury_main->c);

  printf("Dostep do skopiowanych lokalnych wartosci: a = %d, b = %lf, c = %c\n",
  struktura_lokalna.a, struktura_lokalna.b, struktura_lokalna.c);

  return(NULL);
}