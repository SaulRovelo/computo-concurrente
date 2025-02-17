//Ejercicio 3
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h> //Podemos dormir los hilos, para los procesos del sistema operativo

typedef struct{
    int inicio;
    int incremento;
    int fin;
    int id;

}parametros_hilo;


void * muestraContador(void *arg){
    //vamos a desemcapsular los valores de la struct, sino no podemos acceder a ella
    parametros_hilo *philo = (parametros_hilo *) arg; //Casteamos

    int inicio = philo->inicio;
    int incremento = philo->incremento;
    int fin = philo->fin;
    int id = philo->id;
    int contador= inicio;

    while (inicio<=fin)
    {
        printf(" \n Yo soy el hilo %d y el contador es: %d", id, contador);

        contador+=incremento;
    }
    

}
int main()
{
    pthread_t hilo1,hilo2; // declaramos el hilo

    parametros_hilo philo1= {1,1,10,1}; //declaramos una estructura 1
    parametros_hilo philo2= {2,2,10,2}; //declaramos una estructura 1

    // philo1.inicio= 1;
    // philo1.incremento=1;
    // philo1.fin=10;
    // philo1.id=1;

    // Creacion del hilo secundario que ejecutara la función muestraContador
    pthread_create(&hilo1, NULL, muestraContador, (void *)&philo1);
    pthread_create(&hilo2,NULL,muestraContador,(void *) &hilo2); //pasamos por referencia pero en la funcion 
    //acceder a esos datos tenemos que castear

}