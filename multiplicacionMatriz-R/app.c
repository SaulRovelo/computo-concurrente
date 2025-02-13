#include <stdio.h>   
#include <pthread.h> // La usaremos para trabajar con hilos 

#define N 3 // Constante para el tamaño de la matriz

// Matriz de N * N, pero por simplicidad del ejercico haremos matrices de 3*3
int A[N][N]= {
    {1,2,3},
    {4,5,6},
    {7,8,9}
};

int B[N][N] = {
    {9, 8, 7},
    {6, 5, 4},
    {3, 2, 1}
};

// Matriz para almacenar el resultado
int C[N][N];


// Funcion para calcular una fila 
void* multiplicacion(void* arg) {
    // Extraemos el argumento
    int fila = *(int*)arg;
    

    // Recorremos todas las columnas de la fila
    for (int col = 0; col < N; col++) {
        C[fila][col] = 0; // Inicializamos la matriz del resultado

        // Realizamos la multiplicacion de la fila de A con las columnas de B
        for (int k = 0; k < N; k++) {
            C[fila][col] += A[fila][k] * B[k][col];
        }
    }

    return NULL; // Finalizamos
}

int main() {
    pthread_t hilo0, hilo1, hilo2; // Declaramos los hilos 

    // Creamos los 3 hilos para cada una de las filas de A

    int fila0 = 0; // fila 1 
    //Creamos el hilo para la fila 1 con sus argumentos correspondientes
    pthread_create(&hilo0, NULL, multiplicacion, &fila0); 

    // &hilo0: Puntero al identificador del hilo (Guardamos su referencia)
    // NULL: porque usamos los atributos por defecto del hilo 
    // multiplicacion: Le pasamos la funcion para ejecutar 
    // &fila0: Pasamos por referencia el numero de la fila 


    int fila1 = 1; // fila 2
    //Creamos el hilo para la fila 2 con sus argumentos correspondientes
    pthread_create(&hilo1, NULL, multiplicacion, &fila1); 

    
    int fila2 = 2; // fila 3
    //Creamos el hilo para la fila 3 con sus argumentos correspondientes
    pthread_create(&hilo2, NULL, multiplicacion, &fila2); 

    // Esperamos a que los hilos terminen
    pthread_join(hilo0, NULL);
    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);

    // For que recorre la matriz resultado para imprimir
    printf("Resultado de la matriz C:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0; 
}

