#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#include"czytelnia.h"


/*** Implementacja procedur interfejsu ***/

int my_read_lock_lock(czytelnia_t* czytelnia_p){
  
}


int my_read_lock_unlock(czytelnia_t* czytelnia_p){
   
}


int my_write_lock_lock(czytelnia_t* czytelnia_p){
  
}


int my_write_lock_unlock(czytelnia_t* czytelnia_p){
    
}

void inicjuj(czytelnia_t* czytelnia_p){

}

void czytam(czytelnia_t* czytelnia_p){

// wypisanie wartości zmiennych kontrolujących działanie: liczby czytelników i pisarzy

// sprawdzenie warunku poprawności i ewentualny exit
// warunek: if( l_p>1 || (l_p==1 && l_c>0) || l_p<0 || l_c<0 ) { printf(...); exit(0); }

    usleep(rand()%300000);
}

void pisze(czytelnia_t* czytelnia_p){

// wypisanie wartości zmiennych kontrolujących działanie: liczby czytelników i pisarzy

// sprawdzenie warunku poprawności i ewentualny exit
// warunek: if( l_p>1 || (l_p==1 && l_c>0) || l_p<0 || l_c<0 ) { printf(...); exit(0); }

    usleep(rand()%300000);
}


