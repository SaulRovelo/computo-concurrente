#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

int pc_main = 0;
int pc_suma = 0;

void suma(std::vector<int> numeros) {
    std::cout << "\nIniciando el proceso de la suma con un PC " << pc_suma << "\n";  
    int s = 0;
    
    
    for (int i = 0; i < numeros.size(); i++) {
        s += numeros[i];
        pc_suma++;
        std::cout << "PC --> " << pc_suma << " Sumando el número " << numeros[i] << " y el total de la suma es " << s << "\n";  
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(500));  
}

int main() {
    std::vector<int> numeros = {1, 2, 3, 4, 5};
    std::cout << "Inicializando la ejecución del programa \n";  
    pc_main++;
    
    suma(numeros);
    
    std::cout << "PC --> " << pc_main << " \n";  
    return 0;  
