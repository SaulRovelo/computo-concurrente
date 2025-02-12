// Los hilos (threads) son unidades de ejecución que permiten realizar tareas en paralelo dentro de un programa.
// Los mutex son mecanismos de sincronización que bloquean el acceso a recursos compartidos 
// para que solo un hilo pueda acceder a ellos a la vez. 

// En este ejercicio, usamos dos hilos para incrementar una variable 'contador' 10,000 veces cada uno. 
// Utilizamos un mutex para asegurar que un hilo termine su tarea antes de que el otro acceda a la variable, 
// evitando que ambos hilos modifiquen 'contador' al mismo tiempo y causando errores.

#include <stdio.h>
#include <pthread.h>

int contador = 1;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;  // Inicializamos el mutex 

void * incremento(void * arg){
    for(int i = 0; i < 10000; ++i) {
        pthread_mutex_lock(&mutex);  // Utilizamos el mutex para bloquear el acceso a la variable
        contador++;
        pthread_mutex_unlock(&mutex);  // Desbloqueamos el mutex para desbloquear el acceso a la variable
    }
    return NULL;
}

int main(){

    //Declaramos los hilos 
    pthread_t hilo1, hilo2; 
    // Creacion de los hilos donde ambos ejecutaran la funcion incremento
    pthread_create(&hilo1, NULL, incremento, NULL); 
    pthread_create(&hilo2, NULL, incremento, NULL); 
    
    // Aquí, los dos hilos están trabajando en paralelo. 
    // El mutex asegura que solo un hilo acceda a la variable 'contador' a la vez, evitando que ambos hilos modifiquen el valor simultáneamente 
    //
    // pthread_join espera a que el hilo especificado termine su ejecución. En este caso, espera que 'hilo1' termine primero 
    // y luego espera que 'hilo2' termine. Sin embargo, esto no determina el orden en que los hilos se ejecutan. 
    pthread_join(hilo1, NULL); 
    pthread_join(hilo2, NULL); 
    
    printf("\nEl valor del contador es: %d\n", contador); //Imprimimos lo que tiene la variable contador
    
    pthread_mutex_destroy(&mutex);  // Destruimos el mutex 
    return 0;
}