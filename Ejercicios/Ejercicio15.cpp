//Ejercicio 6
#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <semaphore> //apartir de la version 20

std::counting_semaphore<1> semaforo(1);
int balance = 0; // Variable global que almacena el balance

// Función que incrementa el balance
// Recibe un puntero a un entero que contiene el número de iteraciones
void* suma(void* arg) {
    int* iteraciones = (int*)arg; // Convertimos el argumento recibido a un entero con puntero 

    for (int i = 0; i < *iteraciones; i++) {
        semaforo.acquire(); // Funciona con un contador, que se le resta 1,
        // Como el valor inicial es 1, al restar se pone en 0, lo que impide
        // que otro hilo acceda hasta que se llame a sem_post(&semaforo) que le suma 1 al contador;
balance += 1; // Incrementamos la variable compartida
        balance += 1; // Incrementamos en 1
        semaforo.release(); // Liberamos el semáforo
    }

    return NULL;
}

// Función que decrementa el balance
// Recibe un puntero a un entero que contiene el número de iteraciones
void* resta(void* arg) {
    int* iteraciones = (int*)arg; // Convertimos el argumento recibido a un entero con puntero 

    for (int i = 0; i < *iteraciones; i++) {
        semaforo.acquire(); // Bloqueamos el acceso a balance
        balance -= 1; // Decrementamos en 1
        semaforo.release(); // Liberamos el semáforo
    }

    return NULL;
}

int main(int argc, char* argv[]) {
    

    pthread_t sumador, restador; // Declaramos los hilos
    int iteraciones = atoi(argv[1]); // Convertimos el argumento del main a entero

    // Creamos y ejecutamos los hilos
    pthread_create(&sumador, NULL, suma, (void*)&iteraciones);
    pthread_create(&restador, NULL, resta, (void*)&iteraciones);

    // Esperamos a que finalicen los hilos antes de finalizar el programa
    pthread_join(sumador, NULL);
    pthread_join(restador, NULL);

    std::cout << "\nLa variable del balance al final es: " << balance << "\n"; // Mostramos la variable balance

    return 0;
}

/*
   Simulamos una operación de concurrencia en la que dos hilos modifican una variable compartida llamada "balance".
   Un hilo se encarga de incrementarla mientras el otro la decrementa, ambos durante un número determinado de iteraciones.
   Para evitar condiciones de carrera, se utiliza un semáforo para que solo un hilo modifique la variable a la vez.

*/
