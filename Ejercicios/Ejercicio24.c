#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 5

#define N 10

int buffer[BUFFER_SIZE];

int count=0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t nolleno = PTHREAD_COND_INITIALIZER;
pthread_cond_t novacio = PTHREAD_COND_INITIALIZER;

void * productor(void *arg){
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < N; i++)
    {
        while (count==BUFFER_SIZE)
        {
            pthread_cond_wait(&nolleno,&mutex); //se bloquea de manera temporal el mutex
        }
    buffer[count++]=i;
    printf("\nEl productor produjo: %d",i);
    pthread_cond_signal(&novacio);
    pthread_mutex_unlock(&mutex);
    //sleep(1);
    usleep(rand()%1000000);
        
    }
    pthread_exit(NULL);
    

}

void * consumidor(void *arg){
    pthread_mutex_lock(&mutex);
    for(int i=0; i<N;++i){
        while (count== 0)
        {
            pthread_cond_wait(&nolleno,&mutex);
            
        }
        int item=buffer[--count];
        printf("\nConsumidor consumio: %d",item);
        pthread_cond_signal(&nolleno);
        pthread_mutex_unlock(&mutex);
        //sleep(2);
        usleep(rand()%1500000);
    }

    pthread_exit(NULL);
}

int main(){

    pthread_t hiloProductor, hiloConsumidor;

    pthread_create(&hiloProductor,NULL,productor,NULL);
    pthread_create(&hiloConsumidor,NULL,consumidor,NULL);


    pthread_join(hiloProductor,NULL);
    pthread_join(hiloConsumidor,NULL);

    pthread_mutex_destroy( &mutex);
    pthread_cond_destroy(&nolleno);
    pthread_cond_destroy(&novacio);

    return 0;

}