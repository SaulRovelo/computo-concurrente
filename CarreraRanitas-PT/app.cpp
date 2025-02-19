#include <iostream>
#include <vector>
#include <thread>


#define INICIO 1
#define META 30

void brinca();

int main(int argc, char* argv[]){

    srand(time(nullptr)); // Inicializamos semilla

    int ranas = std:: atoi(argv[1]); //Convertimo el argumento a entero
    std::cout << "Voy a mandar a competir a " << ranas << " ranas" << std::endl;

    std::vector<std::thread> ranitas(ranas); //Creamos el arreglo de hilos(ranitas)

    //Creamos y ejecutamos los hilos
    for (int i = 0; i < ranas; i++)
    {
        int* id = new int(i+1); //Reservamos memoria dinamica para las ranitas
        ranitas[i] = std::thread(brinca, id); //Creamos y ejecutamos los hilos(ranitas)
    }

    //Esperamos a que todos los hilos terminen antes de finalizar el programa
    //(que las ranitas lleguen a la meta)

    for (int i = 0; i < ranas; i++)
    {
        
        ranitas[i].join();
    }
    
    
    


}