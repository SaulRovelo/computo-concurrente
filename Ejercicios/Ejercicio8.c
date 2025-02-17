//Ejercicio 4
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h> //para memoria dinamica, en este caso para atoi
#include <time.h>

#define inicio 1
#define meta 5

int ganador=-1;

void * brinca(void * arg){

    int * id = (int *) arg;
    int posicion = inicio;
    while (posicion<meta)
    {
        
        posicion+= rand()%10+1; //genera numeros entre 1 y 10
        printf("\nSoy la ranita %d y estoy en la posicion %d",*id,posicion);
        sleep(1);
    }

    if (posicion>=meta&&ganador==-1)
    {
        ganador=*id;
        pthread_exit(NULL);
    }
    

    //printf("He llegado a la meta y soy la ranita %d\n",*id);

    free(id);
    
    return NULL;
}

// [nombre_programa, argv[1], argv[2]]

int main(int argc, char * argv []){ //Vamos a trabajar con parametros del main

    srand(time(NULL)); //para numero aleatorios

    int ranas =atoi(argv[1]);
    printf("Voy a mandar a competir a %d ranas \n",ranas);
    pthread_t ranitas[ranas]; //creamos un arreglo de hilos 

    
    //Creamos los hilos 
    for (int i = 0; i < ranas; i++)
    {
        int *id = malloc(sizeof(int));

        *id =i+1;
        pthread_create(&ranitas[i],NULL,brinca,(void *) id);
    }
    
    //mandamos a esperar al main hasta que terminen los hilos 

    for(int i=0; i<ranas; ++i){
        pthread_join(ranitas[i],NULL);

    }

    printf("\nLa ranita ganadora es %d\n",ganador);
    
    return 0;
}

//0.5 mas si es carrera de ranitas cpp