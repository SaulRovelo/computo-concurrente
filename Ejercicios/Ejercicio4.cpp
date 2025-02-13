#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

int pc_main = 0;
//int pc_suma=0; quitarla como variable global

void suma(std::vector<int>& numeros) {  // Referencia a numeros para evitar copia
    int pc_suma=0;
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
    

    std::thread hilo_suma(suma, std::ref(numeros));  
    std::thread hilo_suma2(suma, std::ref(numeros)); 
    std::thread hilo_suma3(suma, std::ref(numeros));
    
    hilo_suma.join();
    hilo_suma2.join();
    hilo_suma3.join();
    
    std::cout << "PC --> " << pc_main << " \n";  
    return 0; 
}
