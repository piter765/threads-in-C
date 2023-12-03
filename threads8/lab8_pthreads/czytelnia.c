#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#include"czytelnia.h"


/*** Implementacja procedur interfejsu ***/

int my_read_lock_lock(czytelnia_t* czytelnia_p){
    pthread_mutex_lock(&czytelnia_p->mutex);
    if((czytelnia_p->liczba_p > 0) || (czytelnia_p->empty_p != 0)) {
        czytelnia_p->empty_c++;
        pthread_cond_wait(&czytelnia_p->czytelnik, &czytelnia_p->mutex);
        czytelnia_p->empty_c--;
    }
    czytelnia_p->liczba_c++;
    pthread_mutex_unlock(&czytelnia_p->mutex);

    pthread_cond_signal(&czytelnia_p->czytelnik);
}


int my_read_lock_unlock(czytelnia_t* czytelnia_p){
    pthread_mutex_lock(&czytelnia_p->mutex);
    czytelnia_p->liczba_c--;
    pthread_mutex_unlock(&czytelnia_p->mutex);
    if(czytelnia_p->liczba_c == 0) pthread_cond_signal(&czytelnia_p->pisarz);
}


int my_write_lock_lock(czytelnia_t* czytelnia_p){
    pthread_mutex_lock(&czytelnia_p->mutex);
    if(czytelnia_p->liczba_p > 0 || czytelnia_p->liczba_c > 0){
        czytelnia_p->empty_p++;
        pthread_cond_wait(&czytelnia_p->pisarz, &czytelnia_p->mutex);
        czytelnia_p->empty_p--;
    }
    czytelnia_p->liczba_p++;
    pthread_mutex_unlock(&czytelnia_p->mutex);
}


int my_write_lock_unlock(czytelnia_t* czytelnia_p){
    pthread_mutex_lock(&czytelnia_p->mutex);
    czytelnia_p->liczba_p--;
    if(czytelnia_p->empty_c != 0){
        czytelnia_p->empty_c--;
        pthread_cond_signal(&czytelnia_p->czytelnik);
    } else {
        pthread_cond_signal(&czytelnia_p->pisarz);
    }
    pthread_mutex_unlock(&czytelnia_p->mutex);

}

void inicjuj(czytelnia_t* czytelnia_p){
    pthread_mutex_init(&czytelnia_p->mutex, NULL);
    pthread_cond_init(&czytelnia_p->pisarz, NULL);
    pthread_cond_init(&czytelnia_p->czytelnik, NULL);
}

void czytam(czytelnia_t* czytelnia_p){
    // wypisanie wartości zmiennych kontrolujących działanie: liczby czytelników i pisarzy
    printf("liczba czytelników: %d, liczba pisarzy: %d \n", czytelnia_p->liczba_c, czytelnia_p->liczba_p); 
    // sprawdzenie warunku poprawności i ewentualny exit
    if( czytelnia_p->liczba_p > 1 || (czytelnia_p->liczba_p==1 && czytelnia_p->liczba_c > 0) 
        || czytelnia_p->liczba_p < 0 || czytelnia_p->liczba_c < 0 ) { 
        exit(0); 
    }
    usleep(rand()%300000);
}

void pisze(czytelnia_t* czytelnia_p){
    // wypisanie wartości zmiennych kontrolujących działanie: liczby czytelników i pisarzy
    printf("liczba czytelników: %d, liczba pisarzy: %d \n ", czytelnia_p->liczba_c, czytelnia_p->liczba_p); 
    // sprawdzenie warunku poprawności i ewentualny exit
    if( czytelnia_p->liczba_p > 1 || (czytelnia_p->liczba_p==1 && czytelnia_p->liczba_c > 0) 
        || czytelnia_p->liczba_p < 0 || czytelnia_p->liczba_c < 0 ) { 
        exit(0); 
    }
    usleep(rand()%300000);
}


