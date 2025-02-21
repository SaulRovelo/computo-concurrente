//Ejercicio 6
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int balance=0; // Variable global que almacena el balance

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // Declaración de un mutex para proteger el acceso concurrente a la variable balance

// Función que incrementa el balance
// Recibe un puntero a un entero que contiene el numero de iteraciones
void * suma(void * arg){
    int *iteraciones= (int *)arg; //Casteamos: Convertimos el argumento recibido a un entero con puntero 

    for (int i = 0; i < *iteraciones; i++)
    {
        pthread_mutex_lock(&mutex); // Bloqueamos el mutex, esto hace que solo el hilo actual tenga acceso a la variable balanceo
        balance+=1; //Incrementamos en 1
        pthread_mutex_unlock(&mutex); // Desbloqueamos el mutex y se vuelve tener acceso a la variable
    }
    
    return NULL;
}

// Función que decrementa el balance
// Recibe un puntero a un entero que contiene el numero de iteraciones
void * resta(void * arg){
    int *iteraciones= (int *)arg; //Casteamos: Convertimos el argumento recibido a un entero con puntero 
    for (int i = 0; i < *iteraciones; i++)
    {
        pthread_mutex_lock(&mutex); // Bloqueamos el mutex, esto hace que solo el hilo actual tenga acceso a la variable balanceo
        balance-=1; //Incrementamos en 1
        pthread_mutex_unlock(&mutex); // Desbloqueamos el mutex y se vuelve tener acceso a la variable
    }

    return NULL;

}

int main(int argc,char * argv[]){

    pthread_t sumador,restador; //Declaramos los hilos
    int interaciones=atoi(argv[1]); //Convertimos el argumento del main a entero

    //Creamos y ejecutamos los hilos
    pthread_create(&sumador,NULL,suma,(void *)&interaciones);
    pthread_create(&sumador,NULL,resta,(void *)&interaciones);

    //Esperamos a que finalice los hilos antes de finalizar el programa
    pthread_join(sumador, NULL); 
    pthread_join(restador, NULL); 
    
    printf("\nLa variable del balanceo al final es:%d\n",balance); //Mostramos la variable balanceo


}

/*
   Simulamos una operación de concurrencia en la que dos hilos modifican una variable compartida llamada "balanceo".
   Un hilo se encarga de incrementarla mientras el otro la decrementa, ambos durante un número determinado de iteraciones.
   Para evitar condiciones de carrera, se utiliza un mutex que garantiza que solo un hilo modifique la variable a la vez.
   Al final del programa, el balanceo debería ser 0, ya que las operaciones de suma y resta deberían compensarse entre sí.
*/