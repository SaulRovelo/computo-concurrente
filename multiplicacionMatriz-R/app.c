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
    free(arg); // Liberamos la memoria 

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