//Ejercicio 6 modificado
#include <iostream>
#include <thread>
#include <mutex>

std ::mutex mtx; // Declaración de un mutex para proteger el acceso concurrente a la variable balance
int balanceo=0; // Variable global que almacena el balance

// Función que incrementa el balance
// Recibe como parametro el numero de iteraciones que realizará
void suma(int iteraciones){
    for (int i = 0; i < iteraciones; i++)
    {
        mtx.lock(); // Bloqueamos el mutex, esto hace que solo el hilo actual tenga acceso a la variable balanceo
        balanceo+=1; //Incrementamos en 1
        mtx.unlock(); // Desbloqueamos el mutex y se vuelve tener acceso a la variable
    }
    
}

// Función que decrementa el balance
// Recibe como parametro el numero de iteraciones que realizará
void resta(int iteraciones){
    for (int i = 0; i < iteraciones; i++)
    {
        mtx.lock(); // Bloqueamos el mutex, esto hace que solo el hilo actual tenga acceso a la variable balanceo
        balanceo-=1; //Incrementamos en 1
        mtx.unlock(); // Desbloqueamos el mutex y se vuelve tener acceso a la variable
    }
    
}

int main(int arg,char * argv[]){
    int iteraciones= std:: atoi(argv[1]); //Convertimos el argumento del main a entero

     //Creamos y ejecutamos los hilos
    std::thread hilo1(suma,iteraciones);
    std::thread hilo2(resta,iteraciones);

    //Esperamos a que finalice los hilos antes de finalizar el programa
    hilo1.join();
    hilo2.join();

   

    std:: cout<<"\nLa variable del balanceo al final es"<<balanceo;  //Mostramos la variable balanceo


}
/*
   Simulamos una operación de concurrencia en la que dos hilos modifican una variable compartida llamada "balanceo".
   Un hilo se encarga de incrementarla mientras el otro la decrementa, ambos durante un número determinado de iteraciones.
   Para evitar condiciones de carrera, se utiliza un mutex que garantiza que solo un hilo modifique la variable a la vez.
   Al final del programa, el balanceo debería ser 0, ya que las operaciones de suma y resta deberían compensarse entre sí.
*/