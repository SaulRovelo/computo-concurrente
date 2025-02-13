#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

int pc=0;

void ejecutaInstruccion(std::string instruccion) {
    std::cout << "PC: " << pc << " Ejecutando: " << instruccion << "\n";  
    pc++;
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); 
}


int main() {

    std::vector<std::string> instrucciones = {
        "Cargar datos del proceso A",
        "Cargar datos del proceso B",
        "Sumar los datos del proceso A",
        "Multiplicar los datos del proceso B",
        "Sumar los resultados del proceso A con los datos del proceso B"
    };

    
    for (auto& instruccion : instrucciones) {  
        ejecutaInstruccion(instruccion);  
    }

    return 0;
}
