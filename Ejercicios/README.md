# Computo Concurrente

## 🚀 Introducción

En esta sección se presentan ejercicios prácticos relacionados con los principales mecanismos de concurrencia. Los ejemplos muestran el uso de hilos, mutex, variables de condición, semáforos y barreras, implementados tanto en C como en C++.

---

## 🧵 Hilos (Threads)

Los hilos (threads) son unidades de ejecución que permiten realizar tareas en paralelo dentro de un programa. Los hilos comparten memoria y recursos del proceso principal, lo que hace necesario implementar mecanismos de sincronización para evitar conflictos o condiciones de carrera.

---

### 📌 Funciones utilizadas en C (Librería: `<pthread.h>`)

- `pthread_t`: tipo de dato que representa un identificador de un hilo.  
- `pthread_create()`: crea un nuevo hilo.  
- `pthread_join()`: espera a que un hilo específico termine su ejecución.

---

## 📜 Declaración en C:

```c
pthread_t hilo;
pthread_create(&hilo, atributos, funcion, argumento );
pthread_join(hilo, NULL);
```

### 🔹 Explicación

- `&hilo`: referencia al hilo que será inicializado.  
- `atributos`: parámetros opcionales del hilo, puede ser `NULL`.  
- `funcion`: función que ejecutará el hilo.  
- `argumento`: argumento suministrado a la función del hilo.  
- `pthread_join(hilo, NULL)`: espera la finalización del hilo.

---

### 📌 Funciones utilizadas en C++ (Librería: `<thread>`)

- `std::thread`: crea y controla hilos.  
- `join()`: espera a que el hilo termine su ejecución.

---

## 📜 Declaración en C++:

```cpp
std::thread hilo(funcion, argumento);
hilo.join();
```

### 🔹 Explicación

- `std::thread hilo(...)`: crea un hilo que ejecuta la función indicada.  
- `join()`: sincroniza la ejecución y espera la finalización del hilo.

---

## 🔒 Mutex (Mutual Exclusion)

Los **mutex** son mecanismos que garantizan la exclusión mutua, permitiendo que solo un hilo acceda a un recurso compartido en un momento dado.

---

### 📌 Funciones utilizadas en C (Librería: `<pthread.h>`)

- `pthread_mutex_t`: define un mutex.  
- `pthread_mutex_lock()`: bloquea el mutex.  
- `pthread_mutex_unlock()`: desbloquea el mutex.  
- `pthread_mutex_destroy()`: destruye un mutex.

---

## 📜 Declaración en C:

```c
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_lock(&mutex);
// Recurso compartido
pthread_mutex_unlock(&mutex);
```

### 🔹 Explicación

- `pthread_mutex_lock()`: asegura el acceso exclusivo al recurso.  
- `pthread_mutex_unlock()`: libera el acceso al recurso.

---

### 📌 Funciones utilizadas en C++ (Librería: `<mutex>`)

- `std::mutex`: tipo de mutex.  
- `lock()`: bloquea el mutex.  
- `unlock()`: libera el mutex.

---

## 📜 Declaración en C++:

```cpp
std::mutex mtx;

mtx.lock();
// Recurso compartido
mtx.unlock();
```

### 🔹 Explicación

- `lock()`: permite acceso exclusivo al recurso.  
- `unlock()`: lo libera para otros hilos.

---

## ⏱️ Variables de condición (Condition Variables)

Las variables de condición permiten que un hilo espere hasta que una condición lógica se vuelva verdadera.  
Siempre se usan junto con un mutex.

---

### 📌 Funciones utilizadas en C (Librería: `<pthread.h>`)

- `pthread_cond_t`: variable de condición.  
- `pthread_cond_wait()`: bloquea el hilo.  
- `pthread_cond_signal()`: despierta un hilo.  
- `pthread_cond_broadcast()`: despierta a todos los hilos en espera.  
- `pthread_cond_destroy()`: destruye la variable.

---

## 📜 Declaración en C:

```c
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

pthread_mutex_lock(&mutex);

while (condicion == 0) {
    pthread_cond_wait(&cond, &mutex);
}

// Sección protegida

pthread_mutex_unlock(&mutex);
```

### 🔹 Explicación

- `pthread_cond_wait()`: libera el mutex temporalmente y bloquea.  
- `pthread_cond_signal()`: despierta un hilo bloqueado.  
- `pthread_cond_broadcast()`: despierta a todos los hilos.

---

### 📌 Funciones utilizadas en C++ (Librería: `<condition_variable>`)

- `std::condition_variable`  
- `wait()`  
- `notify_one()`  
- `notify_all()`  

---

## 📜 Declaración en C++:

```cpp
std::mutex mtx;
std::condition_variable cv;
bool listo = false;

std::unique_lock<std::mutex> lock(mtx);

cv.wait(lock, [&]{ return listo; });

// Sección protegida
```

### 🔹 Explicación

- `wait()`: bloquea el hilo mientras la condición esté en falso.  
- `notify_one()` y `notify_all()`: despiertan hilos bloqueados.

---

## 🚦 Semáforos

Los semáforos controlan el acceso concurrente mediante un contador entero.  
Pueden ser binarios (0 o 1) o de conteo.

---

### 📌 Funciones utilizadas en C (Librería: `<semaphore.h>`)

- `sem_t`: semáforo.  
- `sem_init()`: inicializa.  
- `sem_wait()`: decrementa y bloquea si es necesario.  
- `sem_post()`: incrementa.  
- `sem_destroy()`: elimina el semáforo.

---

## 📜 Declaración en C:

```c
sem_t semaforo;

sem_init(&semaforo, 0, 1);

sem_wait(&semaforo);
// Sección crítica
sem_post(&semaforo);

sem_destroy(&semaforo);
```

### 🔹 Explicación

- `sem_wait()`: bloquea si el valor es 0.  
- `sem_post()`: desbloquea hilos incrementando el contador.

---

### 📌 Funciones utilizadas en C++ (C++20)

- `std::counting_semaphore`  
- `acquire()`  
- `release()`  

---

## 📜 Declaración en C++:

```cpp
#include <semaphore>

std::counting_semaphore<1> semaforo(1);

semaforo.acquire();
// Sección crítica
semaforo.release();
```

### 🔹 Explicación

- `acquire()`: bloquea mientras no haya permisos.  
- `release()`: libera un permiso.

---

## 🧱 Barreras de sincronización

Las barreras permiten que varios hilos esperen entre sí hasta que todos alcancen un punto específico.

---

### 📌 Funciones utilizadas en C (Librería: `<pthread.h>`)

- `pthread_barrier_t`  
- `pthread_barrier_init()`  
- `pthread_barrier_wait()`  
- `pthread_barrier_destroy()`  

---

## 📜 Declaración en C:

```c
pthread_barrier_t barrera;

pthread_barrier_init(&barrera, NULL, 5);

pthread_barrier_wait(&barrera);
// Código que continúa tras la barrera

pthread_barrier_destroy(&barrera);
```

### 🔹 Explicación

- `pthread_barrier_wait()`: bloquea al hilo hasta que todos lleguen.  

---

### 📌 Funciones utilizadas en C++20 (Librería: `<barrier>`)

- `std::barrier`  
- `arrive_and_wait()`  

---

## 📜 Declaración en C++20:

```cpp
#include <barrier>
#include <thread>
#include <iostream>

std::barrier barrera(5);

void tarea() {
    std::cout << "Hilo listo\n";
    barrera.arrive_and_wait();
    std::cout << "Hilo continuando\n";
}

int main() {
    std::thread hilos[5];
    for (int i = 0; i < 5; i++)
        hilos[i] = std::thread(tarea);

    for (auto &h : hilos)
        h.join();
}
```

### 🔹 Explicación

- `arrive_and_wait()`: sincroniza a todos los hilos antes de continuar.

---

