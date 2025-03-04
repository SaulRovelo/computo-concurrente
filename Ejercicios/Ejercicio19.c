#include <stdio.h>      // Para funciones de entrada/salida, como printf.
#include <pthread.h>    // Para la creación y manejo de hilos POSIX.
#include <unistd.h>     // Para la función sleep, que pausa la ejecución del hilo.


//Declarar el mutex de manera global ayuda a que en cualquier parte del programa lo podamos usar
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

//Declarar la variable de condicion de manera global ayuda a que en cualquier parte del programa lo podamos usar
// La variable de condición se utiliza para que un hilo espere hasta que se cumpla una determinada condicion.
pthread_cond_t condicion = PTHREAD_COND_INITIALIZER;

// Variable global que simula un recurso compartido o "señal".
// Inicialmente es 0, lo que indica que aún no se ha enviado la señal.
int senial_simulada = 0;


void *hilo_secundario(void * arg) {
    // El hilo espera 2 segundos, simulando alguna operación previa antes de enviar la señal.
    sleep(2);

    // El hilo adquiere el mutex para tener acceso exclusivo al recurso compartido.
    // Esto evita que otros hilos modifiquen la variable 'senial_simulada' al mismo tiempo.
    pthread_mutex_lock(&mutex);

    // Se cambia el valor del recurso compartido, indicando que la señal ha sido "enviada".
    senial_simulada = 1;

    // Se imprime un mensaje para informar que se enviará la señal.
    printf("\nTe mandaré la señal\n");

    // Se envía una señal mediante la variable de condición para notificar a otros hilos
    // (en este caso, el hilo principal) que la condición (senial_simulada == 1) se ha cumplido.
    pthread_cond_signal(&condicion); // despertamos al main

    // Se libera el mutex para que otros hilos puedan acceder al recurso compartido.
    pthread_mutex_unlock(&mutex);

    // Finaliza la ejecución del hilo secundario.
    pthread_exit(NULL);
}

int main() {
    pthread_t hilo; // Variable para almacenar el identificador del hilo secundario.

    // Se crea el hilo secundario que ejecutará la función 'hilo_secundario'.
    pthread_create(&hilo, NULL, hilo_secundario, NULL);

    // Se imprime un mensaje para informar que se ha lanzado el hilo secundario
    // y que el hilo principal esperará hasta recibir la señal.
    printf("\nMandé a ejecutar el hilo secundario, y esperaré la señal\n");

    // El hilo principal adquiere el mutex para proteger el acceso al recurso compartido.
    pthread_mutex_lock(&mutex);

    // Sección crítica: el hilo principal espera a que se envíe la señal.
    // Mientras 'senial_simulada' sea 0 (es decir, la señal no se ha enviado), se espera.
    // La función 'pthread_cond_wait' libera el mutex mientras espera y lo vuelve a adquirir
    // cuando se recibe la señal.
    while (senial_simulada == 0)
        pthread_cond_wait(&condicion, &mutex);

    // Una vez que la condición se cumple (la señal es 1), se imprime un mensaje indicando que
    // el hilo principal ha recibido la señal y continúa con la ejecución.
    printf("\nRecibí la señal y continuo con el programa\n");

    // Se libera el mutex ya que se ha terminado de acceder al recurso compartido.
    pthread_mutex_unlock(&mutex);

    // Se espera a que el hilo secundario termine su ejecución.
    pthread_join(hilo, NULL);

    // Se destruyen el mutex y la variable de condición para liberar los recursos asignados.
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condicion);

    return 0;
}
