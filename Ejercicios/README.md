# Computo Concurrente

## 🚀 Introducción

Este repositorio está enfocado en la explicación detallada de los conceptos esenciales del cómputo concurrente junto con ejemplos prácticos codificados en los lenguajes C y C++.

## 🧵 Hilos (Threads)

Los hilos (threads) son unidades de ejecución que permiten realizar tareas en paralelo dentro de un programa. Los hilos comparten memoria y recursos del proceso principal, lo que hace necesario implementar mecanismos de sincronización para evitar conflictos o condiciones de carrera.

### 📌 Funciones utilizadas en C (Librería: `<pthread.h>`)

- **`pthread_t`**: tipo de dato que representa un identificador de un hilo.
- **`pthread_create()`**: crea un nuevo hilo.
- **`pthread_join()`**: espera a que un hilo específico termine su ejecución.

### 📌 Funciones utilizadas en C++ (Librería: `<thread>`)

- **`std::thread`**: crea y maneja hilos.
- **`join()`**: espera a que el hilo específico termine su ejecución.

---

## 📜 Declaración en C:

```c
pthread_t hilo;
pthread_create(&hilo, atributos, funcion, argumento );
pthread_join(hilo, NULL);
```

🔹 Explicación de `pthread_create(&hilo, attr, función, argumento);`

- **`&hilo`**: Referencia al hilo que será inicializado.
- **`atributo`**: Atributos predeterminados del hilo, puede ser `NULL`.
- **`incremento`**: Función que ejecutará el hilo.
- **`argumento`**: Argumento que recibirá la función, puede ser `NULL`.

🔹 Explicación de `pthread_join(hilo, NULL);`

- **`hilo`**: Identificador del hilo cuya ejecución queremos esperar.
- **`NULL`**: Indica que no necesitamos recuperar ningún valor de retorno del hilo al finalizar.

## 📜 Declaración en C++:

```cpp
std::thread hilo(funcion, argumento);
hilo.join();
```
🔹 Explicación de `std::thread hilo(funcion, argumento);`

- **hilo**: Objeto del tipo `std::thread` que maneja el hilo.
- **funcion**: Función que ejecutará el hilo.
- **argumento**: Argumento que recibe la función al ser ejecutada.

🔹 Explicación de `hilo.join();`

- **join()**: Método que espera a que el hilo finalice su ejecución antes de continuar con el resto del programa.

## 🔒 Mutex (Mutual Exclusion)

Los **mutex** (exclusión mutua) son mecanismos utilizados en la programación concurrente para prevenir condiciones de carrera al acceder a recursos compartidos como variables, estructuras de datos o archivos.

### 📌 Funciones utilizadas en C (Librería: `<pthread.h>`)

- **`pthread_mutex_t`**: tipo de dato que representa un mutex.
- **`pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;`** inicializa un mutex.
- **`pthread_mutex_lock()`**: bloquea el mutex para evitar acceso simultáneo al recurso compartido.
- **`pthread_mutex_unlock()`**: desbloquea el mutex, permitiendo que otros hilos accedan al recurso compartido.
- **`pthread_mutex_destroy()`**: destruye un mutex cuando ya no es necesario.

### 📌 Funciones utilizadas en C++ (Librería: `<mutex>`)

- **`std::mutex`**: clase de C++ que representa un mutex.
- **`std::mutex mtx`**: inicializa un mutex.
- **`lock()`**: bloquea el mutex para evitar acceso simultáneo al recurso compartido.
- **`unlock()`**: libera el mutex, permitiendo que otros hilos accedan al recurso compartido.

---

## 📜 Declaración en C:

```c
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_lock(&mutex);
// Recurso compartido
pthread_mutex_unlock(&mutex);
```
### 🔹 Explicación de `pthread_mutex_lock(&mutex);`

- **`pthread_mutex_lock()`**: Bloquea el mutex antes de acceder a un recurso compartido, asegurando que solo un hilo pueda modificarlo en un momento dado.

### 🔹 Explicación de `pthread_mutex_unlock(&mutex);`

- **`pthread_mutex_unlock()`**: Libera el mutex para permitir que otros hilos accedan al recurso compartido.

---

## 📜 Declaración en C++:

```cpp
std::mutex mtx;
mtx.lock();
// Recurso compartido
mtx.unlock();
```
### 🔹 Explicación de `mtx.lock();`

- **`lock()`**: Bloquea el mutex antes de acceder a un recurso compartido para evitar modificaciones concurrentes no controladas.

### 🔹 Explicación de `mtx.unlock();`

- **`unlock()`**: Libera el mutex para que otros hilos puedan acceder al recurso compartido.


