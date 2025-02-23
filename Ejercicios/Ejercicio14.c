//Ejercicio 6
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

// Declaración de un semaforo global para controlar el acceso a la variable compartida
sem_t semaforo;
int balance=0; // Variable global que almacena el balance


// Función que incrementa el balance
// Recibe un puntero a un entero que contiene el numero de iteraciones
void * suma(void * arg){
    int *iteraciones= (int *)arg; //Casteamos: Convertimos el argumento recibido a un entero con puntero 

    for (int i = 0; i < *iteraciones; i++)
    {
        sem_wait(&semaforo); //Trabaja con un contador y resta dependiendo de los lugares //Pasas porque tengo lugares en este caso es 1 y cuando llamamos restamos
        balance+=1; //Incrementamos en 1
        sem_post(&semaforo);
    }
    
    return NULL;
}

// Función que decrementa el balance
// Recibe un puntero a un entero que contiene el numero de iteraciones
void * resta(void * arg){
    int *iteraciones= (int *)arg; //Casteamos: Convertimos el argumento recibido a un entero con puntero 
    for (int i = 0; i < *iteraciones; i++)
    {
        sem_wait(&semaforo);
        balance-=1; //Incrementamos en 1
        sem_post(&semaforo);
    }

    return NULL;

}

int main(int argc,char * argv[]){

    pthread_t sumador,restador; //Declaramos los hilos
    int interaciones=atoi(argv[1]); //Convertimos el argumento del main a entero

    sem_init(&semaforo,0,1);
    //Creamos y ejecutamos los hilos
    pthread_create(&sumador,NULL,suma,(void *)&interaciones);
    pthread_create(&sumador,NULL,resta,(void *)&interaciones);

    //Esperamos a que finalice los hilos antes de finalizar el programa
    pthread_join(sumador, NULL); 
    pthread_join(restador, NULL); 

    sem_destroy(&semaforo);
    
    printf("\nLa variable del balanceo al final es:%d\n",balance); //Mostramos la variable balanceo


}

/*
   Simulamos una operación de concurrencia en la que dos hilos modifican una variable compartida llamada "balanceo".
   Un hilo se encarga de incrementarla mientras el otro la decrementa, ambos durante un número determinado de iteraciones.
   Para evitar condiciones de carrera, se utiliza un mutex que garantiza que solo un hilo modifique la variable a la vez.
   Al final del programa, el balanceo debería ser 0, ya que las operaciones de suma y resta deberían compensarse entre sí.
*/