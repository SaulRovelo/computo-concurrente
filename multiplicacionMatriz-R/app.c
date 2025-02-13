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
    //free(arg); // Liberamos la memoria 

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

int main (){

    pthread_t hilo0, hilo1, hilo2; // Declaramos los hilos

    int fila0 = 0; // fila 1 

    // Creamos el hilo para la fila 1 con sus argumentos correspondientes
    pthread_create(&hilo0, NULL, multiplicacion, &fila0); 

    

    // Esperamos a que el hilo termine
    pthread_join(hilo0, NULL);

   

    // For que recorre la matriz resultado para imprimir
    printf("Resultado C:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
