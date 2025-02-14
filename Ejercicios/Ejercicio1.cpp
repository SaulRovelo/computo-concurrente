#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

int pc=0; //Representa el numero de la instruccion


void ejecutaInstruccion(std::string instruccion) {
    
    std::cout << "PC: " << pc << " Ejecutando: " << instruccion << "\n";  //Imprimimos la instruccion actual
    pc++; //Pasamos a la siguiente instruccion 
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); //Ponmeos 500 milisegundos, simulando 
                                                                //el tiempo de procesamiento de una instruccion
}
// Usamos std::this_thread::sleep_for porque es más preciso y funciona en cualquier sistema operativo.
// sleep(segundos) solo acepta enteros y no es portable en Windows.


int main() {

    std::vector<std::string> instrucciones = {
        "Cargar datos del proceso A",
        "Cargar datos del proceso B",
        "Sumar los datos del proceso A",
        "Multiplicar los datos del proceso B",
        "Sumar los resultados del proceso A con los datos del proceso B"
    };
    // Se usa std::vector<std::string> para almacenar una lista de instrucciones en un arreglo dinamico.
    // Cada instrucción se guarda en un índice del vector, como en un array 
    // Se puede acceder con instrucciones[i], lo que quiere decir que cada instruccion tiene un indice

    
    for (auto& instruccion : instrucciones) {  
        ejecutaInstruccion(instruccion);  

    }

    // Se lee como: "Para cada elemento en instrucciones, guardalo en instruccion y ejecuta el bloque de codigo".
    // - tipo: Se usa auto para deducir el tipo automaticamente.
    // - &: Indica que se pasa por referencia, evitando copias innecesarias.
    // - instruccion: Representa cada elemento del contenedor en cada iteración.
    // - instrucciones: Es la estructura a recorrer (vector, array, lista, etc.).


    return 0; //Finalizacion
}
// El programa simula la ejecución de instrucciones, utilizando un contador de programa (PC) 
// y un vector de instrucciones. Cada instrucción se "ejecuta" con un retraso simulado.
