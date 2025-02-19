//Ejercicio 3
#include <stdio.h> //entrada/salida
#include <pthread.h> //hilos
//#include <time.h>
#include <unistd.h> //Podemos dormir los hilos, para los procesos del sistema operativo (sleep)

//Estructura que nos ayudara a pasar los datos entre los hilos a la funcion muestraContador
typedef struct{
    int inicio; // Valor inicial del contador
    int incremento; // Cantidad en la que se incrementará el contador en cada iteración
    int fin; // Límite hasta donde debe contar
    int id; // Identificador del hilo

}parametros_hilo;


// Función que ejecutará cada hilo para contar según los parámetros recibidos
void * muestraContador(void *arg){
    //vamos a desemcapsular los valores de la struct, sino no podemos acceder a ella
    parametros_hilo *philo = (parametros_hilo *) arg; //Casteamos: Pasamos los argumentos a tipo parametros_hilo

    // Extraemos los valores y los igualamos a su variable correspondiente
    int inicio = philo->inicio;
    int incremento = philo->incremento;
    int fin = philo->fin;
    int id = philo->id;

    int contador = inicio; // Inicializamos el contador

    // Bucle que realiza el conteo desde inicio hasta fin
    while (contador<=fin)
    {
        printf(" \n Yo soy el hilo %d y el contador es: %d", id, contador);

        contador+=incremento; // Incrementamos el contador segun el valor definido
        sleep(1); // Pausamos el hilo por 1 segundo antes de la siguiente iteracion
    }
    

}
int main()
{
    pthread_t hilo1,hilo2; // Declaramos el hilo

    parametros_hilo philo1= {1,1,10,1}; //declaramos una estructura 1
    parametros_hilo philo2= {2,2,10,2}; //declaramos otra estructura 2


    // Creacion de los hilos que ejecutara la función muestraContador
    pthread_create(&hilo1, NULL, muestraContador, (void *)&philo1);
    pthread_create(&hilo2,NULL,muestraContador,(void *) &philo2); //pasamos por referencia (direccion de memoria)
    //pero en la funcion para acceder a esos datos tenemos que castear ()

    //Esperamos a que todos los hilos terminen antes de finalizar el programa
    pthread_join(hilo1,NULL);
    pthread_join(hilo2,NULL);


    printf("\nTerminamos"); //Mensaje para terminar
    return 0;

}

// Este programa simula dos hilos independientes que cuentan hasta 10 
//con diferentes incrementos: uno de uno en uno y otro de dos en dos.