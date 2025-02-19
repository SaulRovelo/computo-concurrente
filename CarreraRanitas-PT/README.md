# 🐸 Carrera de Ranas - Programa en C++ usando Hilos 🐸

## 🚀 Introducción

Este programa simula una carrera de ranas utilizando hilos en C++. Cada "rana" (hilo) avanza de manera aleatoria en la pista hasta llegar a la meta (30 unidades). El objetivo es el uso de hilos en C++ para ejecutar tareas de manera concurrente y para gestionar memoria dinámica para cada hilo.

---

## 🧵 Uso de Hilos en este programa

En este programa, se crean múltiples hilos (uno por cada rana) que corren en paralelo. Cada hilo:

1. Tiene un identificador único (número de la rana).
2. Avanza una cantidad aleatoria entre 1 y 10 unidades en cada ciclo.
3. Simula un retraso de 500 milisegundos entre cada avance para representar el tiempo de ejecución de cada "instrucción".
4. Termina cuando llega a la meta (30 unidades).

Los hilos se gestionan con `std::thread` y la memoria dinámica se maneja usando `new` para asignar un identificador único a cada hilo (rana). Al final, el programa espera a que todos los hilos terminen de ejecutarse con el método `join()`.

---

## 📂 Estructura del Programa

El programa está dividido en dos partes principales:

1. **Función `brinca`**:
    - Se ejecuta en cada hilo.
    - Cada hilo (rana) avanza en la pista de forma aleatoria hasta llegar a la meta.
    - Imprime un mensaje cuando una rana llega a la meta.

2. **Función `main`**:
    - Inicializa los hilos y les asigna tareas.
    - Establece cuántas ranas competirán basándose en el argumento `argv[1]`.
    - Espera a que todos los hilos terminen antes de finalizar el programa.

---

## 🏃‍♂️ Ejecución del Programa

1. Compila el programa con tu compilador C++ favorito (por ejemplo, `g++`):

    ```bash
    g++ -o build/app app.cpp -pthread
    ```

2. Ejecuta el programa pasando el número de ranas como argumento:

    ```bash
    ./build/app 5
    ```

   Esto lanzará 5 hilos (ranas) que competirán entre sí. Cada hilo avanzará hasta la meta, y al final el programa imprimirá qué rana ha llegado primero.

---

## 💡 Posibles Mejoras

- **Sincronización**: Actualmente, los hilos compiten sin ninguna sincronización, lo que podría generar condiciones de carrera en programas más complejos. Se podría usar un **mutex** para que los hilos no se impriman al mismo tiempo.
  
- **Control de Velocidad**: Se podría hacer que las ranas tengan una velocidad de movimiento diferente utilizando variables de velocidad aleatorias para cada hilo.

- **Optimización de Memoria**: En lugar de usar memoria dinámica (`new`), se podría utilizar `std::unique_ptr` o pasar los identificadores directamente por valor para simplificar el manejo de memoria.


---

## 🤝 Contribución

Si deseas contribuir a este proyecto, ¡siéntete libre de hacer un fork y enviar un pull request! Algunas ideas para contribuir incluyen:

- Mejorar la sincronización de los hilos.
- Añadir más funcionalidades, como diferentes tipos de carreras o escenarios.
- Optimizar el código y la gestión de memoria.

---

Gracias por leer y contribuir. ¡Diviértete corriendo con las ranas! 🐸🎉
