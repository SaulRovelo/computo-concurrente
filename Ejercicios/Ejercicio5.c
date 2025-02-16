#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>


// Variable global contador (se podría usar sin ser global, pero se pasa por referencia)
int contador;

// Funcion que ejecuta el hilo secundario
void *muestraContador(void *arg) {
    int *contador = (int *)arg; // Casteo del argumento a un puntero a entero
    
    
    while (*contador < 10) {
        printf("\nEl contador es: %d\n", *contador);
        sleep(1);  // Espera un segundo antes de la siguiente impresión
    }
    
    return NULL; 
}

int main() {
    int contador = 0; // Variable compartida 
    pthread_t hilo1;  //Declaramos el hilo

    // Creacion del hilo secundario que ejecutara la función muestraContador
    pthread_create(&hilo1, NULL, muestraContador, &contador);

    // Bucle en el hilo principal que incrementa el contador
    for (int i = 0; i < 10; i++) {
        printf("sumando el contador\n");
        contador += 1; // Incrementamos el contador 
        sleep(1);  // Se espera un segundo antes de la siguiente suma
    }

    printf("Finalizamos\n");

    // Esperamos a que el hilo secundario termine antes de finalizar el programa
    pthread_join(hilo1, NULL);

    return 0;
}

/*
    El programa simula un proceso donde un hilo secundario (hilo1) muestra 
    el valor de una variable compartida (contador) mientras el hilo principal(main)
    la incrementa. El contador se incrementa hasta un límite de 10, 
    y el hilo secundario imprime su valor en cada iteración.
*/