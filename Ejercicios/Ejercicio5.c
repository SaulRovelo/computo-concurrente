#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

int contador;

void * muestraContador(void *arg) {
    int *contador = (int *)arg; // Casteamos
    while (*contador < 10) {
        printf("\nEl contador es: %d\n", *contador);
        sleep(1);  
    }
    return NULL;
}

int main() {
    int contador = 0;
    pthread_t hilo1;

    pthread_create(&hilo1, NULL, muestraContador, &contador);

   
    for (int i = 0; i < 10; i++) {
        printf("sumando el contador\n");
        contador += 1;
        sleep(1);  
    }

    printf("Finalizamos\n");

    pthread_join(hilo1, NULL); 

    return 0;
}
