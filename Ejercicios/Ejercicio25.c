//Barrera hasta que todods los hilos llegan podran continuar 
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#define NUMHILOS 5
pthread_barrier_t barrera; //Declaramos la barrera

void *fases (void *arg){

    int  id = * (int *)arg;

    printf("\nHilo %d en la fase 1 ...\n",id);
    usleep(rand()% 1000000);
    printf("\nHilo %d termino la fase 1\n",id);

    //sincronizamos con la barrera
    printf("\nHilo %d esperando que todos los hilos terminen la fase 1\n",id);
    pthread_barrier_wait(&barrera); //hasta que todos los hilos lleguen a este punto podran continuar a la fase 2

    printf("\nHilo %d en la fase 2 ...\n",id);
    usleep(rand()% 1000000);
    printf("\nHilo %d termino la fase 2\n",id);

    return NULL;
}

int main(){

    pthread_t hilos[NUMHILOS];
    srand(time(NULL));
    //Para inicializar la barrera
    pthread_barrier_init(&barrera,NULL,NUMHILOS); //inicializamos

    
    for (int i = 0; i < NUMHILOS; i++)
    {
        int *id = (int*)malloc(sizeof(int)); 
        * id =i+1; 
        pthread_create(&hilos[i],NULL,fases,(void *) id);

    }
    
    for (int i = 0; i < NUMHILOS; i++)
    {
        pthread_join(hilos[i],NULL);
    }
    
    pthread_barrier_destroy(&barrera);

}