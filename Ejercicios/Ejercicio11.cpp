//Ejercicio 5 modificado
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

std::vector <int> arreglo; // Vector global que almacenará los valores a procesar



//Funcion que eleva al cuadrado, la cual le pasamos el inicio y el fin del for, junto con el id del hilo
// Recibimos la referencia al vector, inicio, fin y el ID del hilo
void calculaCuadrados(std::vector<int>& arreglo, int inicio, int fin, int id)
{
    for (int i = inicio; i < fin; i++)
    {
        arreglo[i]=arreglo[i]*arreglo[i];
        std::this_thread::sleep_for(std::chrono::seconds(1));  // Simula el tiempo de ejecución de la instrucción
        std::cout<<"\nYo soy el hilo"<<id<<" y el valor que modifique es:"<<arreglo[i]<<"\n";
    }

    
}

int main(int argc, char* argv[]){

    // Convertimos el argumento recibido desde el main a un número entero 
    //que representa el tamaño del arreglo
    int TAMANIO =std:: atoi(argv[1]);
    

    // Creamos un vector dinamico de tamaño TAMANIO
    std::vector<int> arreglo(TAMANIO);


    // Inicializamos el vector con valores del 0 al TAMANIO-1
    for (int i = 0; i < TAMANIO; i++)
    {
        arreglo[i]=i;
    }

    std::cout<<"\nEl arreglo original es:";  //Imprimimos el arreglo original

    //Mostramos el arreglo original
    for (int i = 0; i < TAMANIO; i++)
    {
        std::cout<<arreglo[i]<<" ";
    }
    int mitad=TAMANIO/2; //Calculamos la mitad del arreglo para dividir la carga entre los hilos

    //Creamos los hilos
    // Se usa std::ref(arreglo) para pasar el vector por referencia 
    std::thread hilo1(calculaCuadrados, std::ref(arreglo), 0, mitad, 1);   // Procesa la primera mitad del arreglo (En el bucle empezara de 0 y terminara en la mitad)
    std::thread hilo2(calculaCuadrados, std::ref(arreglo), mitad, TAMANIO, 2); // Procesa la segunda mitad del arregle (En el buclue inicia desde la mitad y llega hasta el final del arreglo 'Tamanio')
    
    //Esperamos a que todos los hilos terminen antes de finalizar el programa
    hilo1.join();
    hilo2.join();

    //Imprimimos el arreglo que contiene los numeros iniciales al cuadrado
    std::cout<<"\nEl arreglo modificado es:";
    for (int i = 0; i < TAMANIO; i++)
    {
        std::cout<<arreglo[i]<<" ";
    }
}

//Este programa simula el procesamiento de un vector dinamico (arreglo) de tamaño 10, dividiéndolo en dos partes 
//y asignando a dos hilos la tarea de elevar al cuadrado los elementos de cada segmento de manera paralela.