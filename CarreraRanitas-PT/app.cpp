#include <iostream>
#include <vector>
#include <thread>


#define INICIO 1
#define META 30

void brinca(void * arg){
    int * id = (int *) arg; //casteamos
    int posicion = INICIO; 
    while (posicion<META) //Cuando la ranita llegue a la meta que es 30 se sale del bucle
    {
        posicion+= rand()%10+1; //genera numeros entre 1 y 10
        std::this_thread::sleep_for(std::chrono::milliseconds(500));  // Simula el tiempo de ejecución de la instrucción
    }
    std::cout << "He llegado a la meta y soy la ranita " << *id << std::endl; //Imprimimos que la ranita a llegado a la meta
}

int main(int argc, char* argv[]){

    srand(time(nullptr)); // Inicializamos semilla para numeros aleatorios

    int ranas = std:: atoi(argv[1]); //Convertimos el argumento a entero
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
        ranitas[i].join();
    
    
    
    


}