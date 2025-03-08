#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t puede_cortar = PTHREAD_COND_INITIALIZER;
pthread_cond_t puede_soldar = PTHREAD_COND_INITIALIZER;
pthread_cond_t puede_pintar = PTHREAD_COND_INITIALIZER;

#define M 5 //Productos a ensamblar

int productos_cortados = 0;
int productos_soldados = 0;
int productos_pintados = 0;

//Ejercicios 21

//Los cortadores no pueden comenzar con un nuevo producto 
//hasta que los pintores hayan terminado el anterior.

void *cortar(void *arg) {
    int  id = * (int *)arg; //casteamos
    

    for (int i = 0; i < M; i++) {
        pthread_mutex_lock(&mutex);

        while (productos_cortados > productos_pintados) {
            pthread_cond_wait(&puede_cortar, &mutex); //Bloquemos el mutex porque no puede a ver mas productos cortados
            //que pintados 
        }

        printf("Cortador %d estamos cortando el producto %d\n",  id, i+1);
        sleep(1);

        productos_cortados++;
        pthread_cond_signal(&puede_soldar);//liberamos para que los soldadores puedan soldar 
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

//Los soldadores deben esperar a que los cortadores finalicen 
//antes de comenzar a ensamblar.
void *soldar(void *arg) {

    int  id = * (int *)arg;
    

    for (int i = 0; i < M; i++) {

        pthread_mutex_lock(&mutex);

        while (productos_soldados >= productos_cortados) {
            pthread_cond_wait(&puede_soldar, &mutex); //Bloqueamos el mutex cuando llegue el caso de que puede 
            //a ver mas productos soldados que cortados, nuestra condicion nos la impide 
        }
        printf("Soldador %d está ensamblando el producto %d\n",  id, i + 1);
        sleep(1);
        productos_soldados++;

        pthread_cond_signal(&puede_pintar); //liberamos para que los pintores puedan pintar


        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

//Los pintores deben esperar a que los soldadores 
//terminen antes de iniciar la pintura
void *pintar(void *arg) {
    int  id = * (int *)arg;
   
    

    for (int i = 0; i < M; i++) {
        pthread_mutex_lock(&mutex);


        while (productos_pintados >= productos_soldados) {
            pthread_cond_wait(&puede_pintar, &mutex); //Bloqueamos el mutex cuando llegue el caso de que puede 
            //a ver mas productos pintados que soldados, nuestra condicion nos la impide 
        }
        printf("Pintor %d está pintando el producto %d\n",  id, i + 1);
        sleep(1);
        productos_pintados++;

        pthread_cond_signal(&puede_cortar); //Liberamos para que los cortadores puedan cortar


        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}







int main(int argc, char *argv[]) {
    
    //Ejercicio 8

    //Argumentos desde el main
    int num_cortadores = atoi(argv[1]);
    int num_soldadores = atoi(argv[2]);
    int num_pintores = atoi(argv[3]);


    //Ejercicio 20

    //Arreglos para los hilos 
    pthread_t cortadores[num_cortadores], soldadores[num_soldadores], pintores[num_pintores];

    

    // Hilos de cortadores
    for (int i = 0; i < num_cortadores; i++) {

        int *id = (int*)malloc(sizeof(int)); 

        * id =i+1; 
        pthread_create(&cortadores[i],NULL,cortar,(void *) id);
    }

    // Hilos de soldadores
    for (int i = 0; i < num_soldadores; i++) {
        int *id = (int*)malloc(sizeof(int));
        * id = i + 1;
        pthread_create(&soldadores[i], NULL, soldar, (void *)id);
    }

    // Hilos de pintores
    for (int i = 0; i < num_pintores; i++) {
        int *id = (int*)malloc(sizeof(int));
        * id = i + 1;
        pthread_create(&pintores[i], NULL, pintar, (void *)id);
    }




    //Esperamos a que todos los hilos terminen antes de finalizar el programa
    
    for (int i = 0; i < num_cortadores; i++) {
        pthread_join(cortadores[i], NULL);
    }

    
    for (int i = 0; i < num_soldadores; i++) {
        pthread_join(soldadores[i], NULL);
    }

    
    for (int i = 0; i < num_pintores; i++) {
        pthread_join(pintores[i], NULL);
    }


    //Ejercicio 24
    // Liberamos recursos
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&puede_cortar);
    pthread_cond_destroy(&puede_soldar);
    pthread_cond_destroy(&puede_pintar);

    return 0;
}