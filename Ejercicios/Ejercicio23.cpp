#include <iostream>
#include <thread>
#include <chrono>
#include <condition_variable>
#include  <mutex>
std:: mutex mutex;
std::condition_variable variableCondicion;
int sumaPares=0;
int sumaImpares=0;
int numero;

bool par = false;              
bool impar = false;            
bool terminado_pares = false;  
bool terminado_impares = false;

void calculoPares(){
    for (int i = 2; i <= 100; i += 2) { // Sumamos de dos hasta 100 (exclusivo)
        {
            std::lock_guard<std::mutex> lock(mutex);
            numero = i;
            sumaPares += numero;
            par = true;
        }
        variableCondicion.notify_one(); // Notifica al hilo de impresión
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    {
        std::lock_guard<std::mutex> lock(mutex);
        terminado_pares = true;
    }
    variableCondicion.notify_one();
}

void calculoImpares(){
    for (int i = 1; i < 100; i += 2) { // Corrige el incremento a i += 2
        {
            std::lock_guard<std::mutex> lock(mutex);
            numero = i;
            sumaImpares += numero;
            impar = true;
        }
        variableCondicion.notify_one();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    {
        std::lock_guard<std::mutex> lock(mutex);
        terminado_impares = true;
    }
    variableCondicion.notify_one();
}

void imprimir(){
    std::unique_lock<std::mutex> lock(mutex);
    while (true)
    {
        variableCondicion.wait(lock, [] { 
            return par || impar || (terminado_pares && terminado_impares); 
        });

        if (par) {
            std::cout << "Número agregado a la suma de pares: " << numero 
                      << " | Suma parcial de pares: " << sumaPares << std::endl;
            par = false; // Reiniciamos 
        }
        if (impar) {
            std::cout << "Número agregado a la suma de impares: " << numero 
                      << " | Suma parcial de impares: " << sumaImpares << std::endl;
            impar = false; // Reiniciamos 
        }

        if (terminado_pares && terminado_impares) {
            std::cout << "\nAmbos hilos terminaron y la suma par es " << sumaPares 
                      << " y la suma impar es " << sumaImpares << std::endl;
            break;
        }
        
    }
    
   
    
}





int main(){

    //Creamos y ejecutamos los hilos

    std::thread hilos_pares(calculoPares);
    std::thread hilos_impares(calculoImpares);
    std::thread hilos_impresion(imprimir);

    hilos_pares.join();
    hilos_impares.join();
    hilos_impresion.join();
    
    return 0;


}

