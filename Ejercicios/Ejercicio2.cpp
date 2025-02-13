#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

int pc = 0;

void ejecutaInstruccionA(std::string instruccion) {
    std::cout << "Estoy en la funcion A y el PC es: " << pc << "\n";  
    pc++;
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); 
}

void ejecutaInstruccionB(std::string instruccion) {
    std::cout << "Estoy en la funcion B y el PC es: " << pc << "\n";  
    pc++;
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); 
}

int main() {

    std::cout << "Iniciando el programa :)\n";  
    std::cout << "PC -->" << pc << "\n";  
    pc++;  

    
    ejecutaInstruccionA("Instrucción A");
    std::cout << "Regresando el PC a la función A---> " << pc << "\n";  
    pc++;

    // Llamar a la función B con una instrucción
    ejecutaInstruccionB("Instrucción B");
    std::cout << "Regresando el PC a la función B---> " << pc << "\n";  
    pc++;

    std::cout << "El PC final es: " << pc << " \n";  

    return 0;  
}
