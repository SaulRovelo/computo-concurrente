#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

int pc_main = 0; // Contador de instrucciones en la función main
int pc_suma = 0; // Contador de instrucciones en la función suma

void suma(std::vector<int> numeros) {
    // Se recibe el vector numeros (lista) de los numeros a sumar
    std::cout << "\nIniciando el proceso de la suma con un PC " << pc_suma << "\n";  
    int s = 0; //Variable para almacenar la suma
    
    // Iteramos sobre cada numero en el vector (numeros) utilizando el tamaño del vector (numeros.size())
    for (int i = 0; i < numeros.size(); i++) {
        s += numeros[i]; // Accedemos a cada elemento del vector y lo sumamos al total acumulado
        pc_suma++; // Incrementamos el contador de instrucciones de la función suma
        std::cout << "PC --> " << pc_suma << " Sumando el número " << numeros[i] << " y el total de la suma es " << s << "\n";  
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(500));   // Simula el tiempo de ejecución de la instrucción
}

int main() {
    std::vector<int> numeros = {1, 2, 3, 4, 5}; //vector (Lista)de numeros a sumar 
    std::cout << "Inicializando la ejecución del programa \n";  
   
    
    suma(numeros);

    pc_main++; // Aumentamos el contador de instrucciones de main
    
    std::cout << "PC --> " << pc_main << " \n";  // Imprimimos el numero de instrucciones de main
    return 0;  
}

// El programa ejecuta de manera secuencial la suma de una lista de numeros. 
// La funcion suma procesa los numeros uno por uno y actualiza un contador de instrucciones (pc_suma). 
//En elmain también lleva un contador (pc_main) para seguir el orden de ejecución.