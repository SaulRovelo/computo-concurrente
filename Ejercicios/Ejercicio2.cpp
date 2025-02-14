#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

int pc = 0; //Representa el numero de la instruccion

void ejecutaInstruccionA(std::string instruccion) {
    std::cout << "Estoy en la funcion A y el PC es: " << pc << "\n";  //Imprimimos 
    pc++; // Incrementa el PC
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Simula el tiempo de ejecución de la instrucción
}

void ejecutaInstruccionB(std::string instruccion) {
    std::cout << "Estoy en la funcion B y el PC es: " << pc << "\n";  //Imprimimos 
    pc++; // Incrementa el PC
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Simula el tiempo de ejecución de la instrucción
}

int main() {

    std::cout << "Iniciando el programa :)\n";  
    std::cout << "PC -->" << pc << "\n";  //El contador de instrucciones esta en 0
    pc++;  // Inicia el contador de instrucciones

    // Llama a la funcion A con una instruccion (no tiene impacto directo en la funcion, solo simula la ejecucion).
    ejecutaInstruccionA("Instrucción A");
    std::cout << "Regresando el PC a la función A---> " << pc << "\n";  
    pc++; // Incrementa el PC después de regresar de la función A.


     // Llama a la funcion B con una instruccion (no tiene impacto directo en la funcion, solo simula la ejecucion).
    ejecutaInstruccionB("Instrucción B");
    std::cout << "Regresando el PC a la función B---> " << pc << "\n";  
    pc++; // Incrementa el PC despues de regresar de la función B

    std::cout << "El PC final es: " << pc << " \n";  // Imprime el valor final del PC

    return 0;  
}
// El programa simula la ejecucion de instrucciones, utilizando un contador de programa (PC) 
// que sigue el flujo de ejecución. Las funciones A y B simulan el procesamiento con retrasos.
