#include <iostream>      // Para operaciones de entrada/salida (std::cout)
#include <thread>        // Para crear los hilos
#include <vector>        // Para almacenar los hilos en contenedores dinámicos
#include <mutex>         // Para utilizar mutex 
#include <semaphore>     // Para utilizar semáforos

//Este mutex nos ayudara a que solo un hilo a la vez pueda modificar una varaible compartida
std::mutex mutex_lectores;


//Este semaforo nos ayudara a que cuando este "escribiendo" el escritor, ningun lector o otro escritor iterfieran
//Es por eso que tiene el 1, porque solo un hilo-escritor tendra acceso. 
std::counting_semaphore<1> semaforo_escritor(1);

// Variable para tener un orden con los lectores
int contador_lectores = 0;

// Función que simula el comportamiento de un lector.

void lector(int id_hilo) {
    //Bloqueamos para que solo el hilo en ejecucion tenga acceso al contador
    mutex_lectores.lock();
    contador_lectores++;   // Incrementamos el contador de lectores activos.

   
    //El objetivo de esta condicional es que si hay al menos un lector, pedira permiso al semaforo, haciendo
    //que los escritores no puedan acceder a el libro 
    if (contador_lectores == 1) {
        semaforo_escritor.acquire(); //Le pide permiso al semaforo
        //Es decir si el semaforo esta en 1 podra acceder y lo pondra en 0
    }
    // Se libera el mutex para permitir que otros lectores puedan modificar el contador.
    mutex_lectores.unlock();

    //simulación de la lectura del libro.
    std::cout << "El lector " << id_hilo << " esta ocupando el libro\n";
    // Se simula el tiempo de lectura; el hilo se detiene durante 1 segundo.
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "El lector " << id_hilo << " terminó de leer el libro\n";

    // Se termina la lectura y actualizamos el contador, restamos al lector que ya termino de leer
    mutex_lectores.lock();
    contador_lectores--;   // Decrementamos el contador de lectores activos.

    // Si este es el último lector en salir, se libera el semáforo para permitir el acceso a los escritores.
    if (contador_lectores == 0) {
        semaforo_escritor.release();  // libera el permiso que que le habiamos pedido al semafor
        //es decir si el ya es el ultimo lector, volveremos a poner al semaforo en 1 para que el escritor tenga acceso
    }
    // Se libera el mutex 
    mutex_lectores.unlock();
}


void escritor(int id_hilo) {
    // El escritor necesita tener acceso exclusivo al recurso:
    // Entonces desde que un hilo escritor se ejecuta debemos poner el semaforo en 0 para que nadie tenga acceso al libro
    semaforo_escritor.acquire();

    // Se bloquea el mutex para asegurar que ningún lector esté modificando el contador en este momento.
    mutex_lectores.lock();

    // Simulacion del escritor escribiendo
    std::cout << "\nEl escritor " << id_hilo << " está escribiendo, nadie puede tocar el libro\n";
    // Se simula el tiempo de escritura; el hilo se detiene durante 2 segundos.
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "\nTerminé de escribir y soy " << id_hilo << "\n";

    // Una vez terminada la escritura, se libera el semáforo para que otros escritores (o el primer lector) puedan acceder.
    semaforo_escritor.release();
    // Se libera el mutex, permitiendo que los lectores puedan modificar el contador.
    mutex_lectores.unlock();
}


int main(int argc, char * argv[]) {

    int lectores, escritores;

    //Obtenemos los argumentos del main
    lectores = std::atoi(argv[1]);
    escritores = std::atoi(argv[2]);

    // Se definen vectores para almacenar los hilos de lectores y escritores.
    std::vector<std::thread> hilos_lectores;
    std::vector<std::thread> hilos_escritores;

    // Creamos los hilos de escritores y lectores con ayuda del argumento desde el main
    for (int i = 0; i < lectores; ++i) {
        hilos_lectores.push_back(std::thread(lector, i));
    }

    for (int i = 0; i < escritores; ++i) {
        hilos_escritores.push_back(std::thread(escritor, i));
    }
    
    
    //Esperamos que todos los hilos terminen antes de finalizar el programa
    for (auto & hilo : hilos_escritores) {
        hilo.join();
    }
   
    for (auto & hilo : hilos_lectores) {
        hilo.join();
    }

    // Fin del programa.
    return 0;
}

//Objetivos:
// Función lector:

// Objetivo: Permitir que varios lectores accedan simultáneamente al recurso, siempre que ningún escritor esté modificándolo.
// Cómo funciona:

// 1. Se incrementa un contador protegido por un mutex.
// 2. Si es el primer lector, adquiere el semáforo, bloqueando la entrada de escritores.
// 3. Realiza la "lectura" (se simula con una pausa).
// 4. Al terminar, decrementa el contador; si es el último lector, libera el semáforo para que los escritores puedan acceder.

// Función escritor:

// Objetivo: Garantizar que un escritor acceda de forma exclusiva al recurso, impidiendo que otros escritores o lectores interfieran.
// Cómo funciona:
// 1. Adquiere el semáforo, lo que bloquea a otros escritores y evita la entrada de lectores.
// 2. Realiza la "escritura" (simulada con una pausa).
// 3. Libera el semáforo, permitiendo que otros hilos accedan al recurso.

//Nota ejecutamos de esta manera, por lo de la declaracion del semaforo.
//g++ -o build/Ejercicio17 Ejercicio17.cpp -std=c++20 -pthread