//Ejercicio 6
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

sem_t semaforo; // Declaramos un semaforo para controlar el acceso a la variable balance.
int balance=0; // Variable global que almacena el balance

// Función que incrementa el balance
// Recibe un puntero a un entero que contiene el numero de iteraciones
void * suma(void * arg){
    int *iteraciones= (int *)arg; //Casteamos: Convertimos el argumento recibido a un entero con puntero 

    for (int i = 0; i < *iteraciones; i++)
    {
        sem_wait(&semaforo); // Esperamos a que el semaforo permita el acceso. (Restamos 1 al contador del semaforo)
        balance+=1; //Incrementamos en 1
        sem_post(&semaforo); // Liberamos el semaforo para que otro hilo pueda acceder.
    }
    
    return NULL;
}

// Función que decrementa el balance
// Recibe un puntero a un entero que contiene el numero de iteraciones
void * resta(void * arg){
    int *iteraciones= (int *)arg; //Casteamos: Convertimos el argumento recibido a un entero con puntero 
    for (int i = 0; i < *iteraciones; i++)
    {
        sem_wait(&semaforo); // Esperamos a que el semaforo permita el acceso. (Restamos 1 al contador del semaforo)
        balance-=1; //Decrementamos en 1
        sem_post(&semaforo); // Liberamos el semaforo para que otro hilo pueda acceder.
    }

    return NULL;

}

int main(int argc,char * argv[]){

    pthread_t sumador1, sumador2, restador1, restador2; //Declaramos los hilos 
    int iteraciones=atoi(argv[1]); //Convertimos el argumento del main a entero

    // Inicializamos el semaforo con valor 4, permitiendo que los 4 hilos trabajen simultaneamnete
    sem_init(&semaforo,0,4); 

    //Creamos y ejecutamos los hilos
     pthread_create(&sumador1, NULL, suma, (void *)&iteraciones);
     pthread_create(&sumador2, NULL, suma, (void *)&iteraciones);
     pthread_create(&restador1, NULL, resta, (void *)&iteraciones);
     pthread_create(&restador2, NULL, resta, (void *)&iteraciones);

    //Esperamos a que finalice los hilos antes de finalizar el programa
    pthread_join(sumador1, NULL);
    pthread_join(sumador2, NULL);
    pthread_join(restador1, NULL);
    pthread_join(restador2, NULL);

    sem_destroy(&semaforo); //Destruimos el semaforo
    
    printf("\nLa variable del balanceo al final es:%d\n",balance); //Mostramos la variable balanceo


}

