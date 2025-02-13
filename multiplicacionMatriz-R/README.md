# 🧵 Multiplicación de Matrices Usando Hilos en C

## 📌 Introducción

Este programa implementa la multiplicación de matrices utilizando hilos en C con la librería `pthread.h`. Se emplean hilos para calcular cada fila de la matriz resultante de manera concurrente 🚀

## 🚀 Uso de Hilos en la Multiplicación de Matrices

Un **hilo** es una unidad de ejecución dentro de un proceso que permite realizar tareas de forma **concurrente** (alternando su ejecución) o **paralela** (ejecutándose simultáneamente en múltiples núcleos). Todos los hilos de un proceso comparten recursos como la memoria y las variables globales, lo que facilita la comunicación pero puede generar conflictos. 🏎️💨

En este programa:

✅ Se crea un **hilo por cada fila** de la matriz resultado.

✅ Cada hilo ejecuta la función `multiplicacion`, que realiza la operación de multiplicación para una fila específica.

✅ Se usa `pthread_create` para lanzar los hilos y `pthread_join` para esperar a que terminen antes de imprimir la matriz resultante.

✅ **No se usa mutex** ya que cada hilo trabaja en una fila independiente, evitando conflictos en memoria compartida. 🔒❌

---

## 📂 Estructura del Programa

El programa consta de las siguientes secciones:

📌 **Inclusión de librerías**: `#include <stdio.h>` y `#include <pthread.h>`.

📌 **Definición de matrices**: `A`, `B` (matrices de entrada) y `C` (resultado).

📌 **Función `multiplicacion`**: Calcula el producto de una fila de `A` con todas las columnas de `B` y almacena el resultado en la matriz `C`.  

📌 **Función `main`**:  
   - Se **crean los hilos**, uno por cada fila de la matriz `A`.  
   - Se **espera** a que los hilos finalicen.  
   - Se **imprime** la matriz resultado `C`.   

---

## ⚙️ Ejecución del Programa

### 🔨 Compilar:
```bash
gcc app.c -o build/app -pthread
```

### ▶️ Ejecutar:
```bash
./app
```

### 📌 Salida esperada:
```
Resultado de la matriz C:
30 24 18
84 69 54
138 114 90
```

---

## 💡 Posibles Mejoras

🔄 Usar un **bucle** para crear los hilos en lugar de hacerlo manualmente.

⏳ Implementar otro **bucle** para esperar a que los hilos terminen.

📦 Utilizar **memoria dinámica** en vez de variables estáticas.

🎛️ Permitir que el usuario **ingrese las matrices** en vez de tenerlas predefinidas.

---

## 🤝 Contribución

Si deseas mejorar este proyecto, puedes hacer un **fork** y enviar un **pull request** con tus mejoras. 🚀


