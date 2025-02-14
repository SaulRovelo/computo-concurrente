#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

int pc_main = 0;
//int pc_suma=0; SE quito porque habia interferencias con los hilos y la puse en local
// Cuando se usaba como variable global, varios hilos intentaban acceder y modificar su valor al mismo tiempo,
// lo que causaba problemas de sincronización. 

void suma(std::vector<int> numeros) {  
    // Se recibe el vector numeros (lista) de los numeros a sumar
    int pc_suma=0; // Cambio a local
    std::cout << "\nIniciando el proceso de la suma con un PC " << pc_suma << "\n";  
    int s = 0; //Variable para almacenar la suma
    
    // Iteramos sobre cada numero en el vector (numeros) utilizando el tamaño del vector (numeros.size())
    for (int i = 0; i < numeros.size(); i++) {
        s += numeros[i]; // Accedemos a cada elemento del vector y lo sumamos al total acumulado
        pc_suma++; // Incrementamos el contador de instrucciones de la función suma
        std::cout << "PC --> " << pc_suma << " Sumando el número " << numeros[i] << " y el total de la suma es " << s << "\n";  
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(500));  // Simula el tiempo de ejecución de la instrucción
}

int main() {
    std::vector<int> numeros = {1, 2, 3, 4, 5}; //vector (Lista)de numeros a sumar 
    std::cout << "Inicializando la ejecución del programa \n";  

    pc_main++; // Aumentamos el contador de instrucciones de main
    

    // Creación de los hilos donde cada uno ejecutará la función 'suma' y se les pasa la lista 'numeros'.
    // Usamos 'std::ref' para pasar la lista 'numeros' por referencia a cada hilo, lo que permite que los hilos 
    // puedan acceder y modificar la lista original sin crear copias innecesarias.
    // Sin 'std::ref', los hilos recibirían una copia de la lista, lo que podría causar resultados inesperados 
    // o innecesarias duplicaciones de datos.
    //
    // Cada hilo ejecutará la misma función 'suma' pero de manera independiente en paralelo.
    std::thread hilo_suma(suma, std::ref(numeros));  
    std::thread hilo_suma2(suma, std::ref(numeros)); 
    std::thread hilo_suma3(suma, std::ref(numeros));
    
    // Aquí, los tres hilos estan trabajando en paralelo. 
    // Al mover la variable pc_suma a local dentro de la función, cada hilo tiene su propia instancia de la variable, evitando interferencias
    //
    // .join se utiliza para que el hilo principal (main) espere a que el hilo especificado termine su ejecución antes de continuar con la siguiente instrucción.
    // Es decir, el hilo principal no continuará hasta que el hilo 'hilo_suma' haya completado su tarea. Esto se repite con 'hilo_suma2' y 'hilo_suma3'
    hilo_suma.join();
    hilo_suma2.join();
    hilo_suma3.join();
    
    std::cout << "PC --> " << pc_main << " \n";  // Imprimimos el numero de instrucciones de main
    return 0; 
}
