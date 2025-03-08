//Modificado usando:Variable condicion, semaforos, barrera y mutex. 
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

#define M 5 //Numero de productos 

// Variables para el mutex y la variable condicion
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t puede_cortar = PTHREAD_COND_INITIALIZER;
pthread_cond_t puede_soldar = PTHREAD_COND_INITIALIZER;
pthread_cond_t puede_pintar = PTHREAD_COND_INITIALIZER;

// Semaforos usados como contadores
sem_t productos_cortados;
sem_t productos_soldados;
sem_t productos_pintados;

// Barrera para sincronizar al final de cada producto
pthread_barrier_t barrera;

//
// Función de los cortadores
//
void *cortar(void *arg) {
    int id = *(int *)arg; //casteamos


    for (int i = 0; i < M; i++) {
        // Para acceder el contador de este semaforo debe estar en 1, por eso asi lo inicializamos, es decir que hay 
        //un producto pintado desde el inicio
        sem_wait(&productos_pintados);
        
        pthread_mutex_lock(&mutex);
        printf("Cortador %d: estamos cortando el producto %d\n", id, i + 1);
        sleep(1); //Simulamos el tiempo que tardamos en cortar
        pthread_mutex_unlock(&mutex);
        
        
        //Incrementamos el contador, es decir que se ha cortado un producto
        sem_post(&productos_cortados);
        pthread_cond_signal(&puede_soldar); //liberamos para que los soldadores puedan soldar 
        
        
        printf("Cortador %d: Esperando que lleguen los demas \n", id);
        pthread_barrier_wait(&barrera); 
         // La barrera sincroniza a todos los hilos (cortadores, soldadores y pintores) para que
        // ningun hilo inicie con el siguiente producto hasta que todos hayan completado el actual.
        
        
    }
    return NULL;
}


// Función de los soldadores

void *soldar(void *arg) {
    int id = *(int *)arg;
    

    for (int i = 0; i < M; i++) {
        // Esperamos a que el contador sea al menos 1, es decir a que se haya cortado un producto 
        sem_wait(&productos_cortados);
        
        pthread_mutex_lock(&mutex);
        printf("Soldador %d: estamos ensamblando el producto %d\n", id, i + 1);
        sleep(1); //simulamos el tiempo de soldar
        pthread_mutex_unlock(&mutex);
        
        
        //Aumentamos el contador de productos_soldados, es decir indicamos que se ha soldado un producto
        sem_post(&productos_soldados);
        pthread_cond_signal(&puede_pintar); //liberamos para que los pintores puedan pintar 
        
        
        printf("Soldador %d: Esperando que lleguen los demas \n", id);
        pthread_barrier_wait(&barrera);
         // La barrera sincroniza a todos los hilos (cortadores, soldadores y pintores) para que
        // ningun hilo inicie con el siguiente producto hasta que todos hayan completado el actual.
        
        
        
    }
    return NULL;
}


// Función de los pintores

void *pintar(void *arg) {
    int id = *(int *)arg;
    

    for (int i = 0; i < M; i++) {
        
        // Esperamos a que el contador sea al menos 1, es decir a que se haya soldado un producto 
        sem_wait(&productos_soldados);
        
        pthread_mutex_lock(&mutex);
        printf("Pintor %d: estamos pintando el producto %d\n", id, i + 1);
        sleep(1); //Simulamos la pintada
        pthread_mutex_unlock(&mutex);
        
        
        //Aumentamos el contador de productos_pintados, es decir indicamos que se ha pintado un producto
        sem_post(&productos_pintados);
        pthread_cond_signal(&puede_cortar); //liberamos para que los pintores puedan pintar 
        
        printf("Pintor %d: Esperando que lleguen los demas\n", id);
        pthread_barrier_wait(&barrera);
        // La barrera sincroniza a todos los hilos (cortadores, soldadores y pintores) para que
        // ningun hilo inicie con el siguiente producto hasta que todos hayan completado el actual.
        
        
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    
    //Recibimos los argumentos del main
    int num_cortadores = atoi(argv[1]);
    int num_soldadores = atoi(argv[2]);
    int num_pintores = atoi(argv[3]);
    int total_hilos = num_cortadores + num_soldadores + num_pintores;

   //Arreglos para los hilos 
   pthread_t cortadores[num_cortadores], soldadores[num_soldadores], pintores[num_pintores];

    // Inicialización de semaforos:

    sem_init(&productos_cortados, 0, 0);
    sem_init(&productos_soldados, 0, 0);
    sem_init(&productos_pintados, 0, 1); //Iniciamos en 1 para que el ciclo de cortar pueda iniciar

    // Inicializamos la barrera 
    pthread_barrier_init(&barrera, NULL, total_hilos);

    // hilos de cortadores
    for (int i = 0; i < num_cortadores; i++) {
        int *id = (int*)malloc(sizeof(int)); 

        * id =i+1; 
        pthread_create(&cortadores[i], NULL, cortar, id);
    }

    // hilos de soldadores
    for (int i = 0; i < num_soldadores; i++) {
        int *id = (int*)malloc(sizeof(int)); 

        * id =i+1; 
        pthread_create(&soldadores[i], NULL, soldar, id);
    }

    // hilos de pintores
    for (int i = 0; i < num_pintores; i++) {
        int *id = (int*)malloc(sizeof(int)); 

        * id =i+1; 
        pthread_create(&pintores[i], NULL, pintar, id);
    }

   //Esperamos a que todos los hilos terminen antes de finalizar el programa
    for (int i = 0; i < num_cortadores; i++)
        pthread_join(cortadores[i], NULL);


    for (int i = 0; i < num_soldadores; i++)
        pthread_join(soldadores[i], NULL);


    for (int i = 0; i < num_pintores; i++)
        pthread_join(pintores[i], NULL);



     // Liberamos recursos
    sem_destroy(&productos_cortados);
    sem_destroy(&productos_soldados);
    sem_destroy(&productos_pintados);
    pthread_barrier_destroy(&barrera);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&puede_cortar);
    pthread_cond_destroy(&puede_soldar);
    pthread_cond_destroy(&puede_pintar);


    return 0;
}
