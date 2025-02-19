//Ejercicio 5
#include <stdio.h> // Entrada/salida estandar
#include <pthread.h> //Hilos
#include <unistd.h> //para el sleep (bajo nivel en el sistema)
#include <stdlib.h> //para memoria dinamica, en este caso para atoi
#include <time.h> //Para generar numeros aleatorios


#define inicio 1 //Variable global para inicializar la posicion
#define meta 30 //Variable global para la meta

int ganador=-1; // Variable global para almacenar la ranita ganadora, inicializada en -1 (sin ganador aun)

void * brinca(void * arg){

    int * id = (int *) arg; //casteamos pasamos de char a int
    int posicion = inicio; 

    while (posicion<meta) //Cuando la ranita llegue a la meta que es 30 se sale del bucle
    {
        
        posicion+= rand()%10+1; //genera numeros entre 1 y 10
        printf("\nSoy la ranita %d y estoy en la posicion %d",*id,posicion);
        sleep(1); // Pausamos la ejecución por 1 segundo
    }

     // Si la ranita llega a la meta y aún no hay un ganador, se asigna como ganadora
    if (posicion>=meta&&ganador==-1)
    {
        ganador=*id; // La ranita actual se registra como la ganadora
        pthread_exit(NULL); //Finalizamos 
    }
    

    free(id); //Liberamos memoria
    
    return NULL;
}



int main(int argc, char * argv []){ //Vamos a trabajar con parametros del main

    srand(time(NULL)); //para numero aleatorios

    int ranas =atoi(argv[1]); //Convertimos el argumento a entero
    printf("Voy a mandar a competir a %d ranas \n",ranas);
    pthread_t ranitas[ranas]; //creamos un arreglo de hilos 

    
    //Creamos y ejecutamos los hilos
    for (int i = 0; i < ranas; i++)
    {
        int *id = malloc(sizeof(int)); //Reservamos memoria dinamica

        *id =i+1; //cada ranita tendra su identificador unico
        pthread_create(&ranitas[i],NULL,brinca,(void *) id); //Creamos y ejecutamos los hilos(ranitas)
    }
    
    //Esperamos a que todos los hilos terminen antes de finalizar el programa
    //(que las ranitas lleguen a la meta)
    for(int i=0; i<ranas; ++i){
        pthread_join(ranitas[i],NULL);

    }

    printf("\nLa ranita ganadora es %d\n",ganador); //Mensaje con la ranita ganadora
    
    return 0;
}

// Simula una carrera de ranas donde cada una avanza de manera aleatoria en hilos separados 
//hasta alcanzar la meta, registrando la primera en llegar como ganadora.