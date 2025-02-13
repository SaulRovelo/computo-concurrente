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
