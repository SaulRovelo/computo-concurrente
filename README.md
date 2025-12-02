# 💻 Cómputo Concurrente en C y C++

Este repositorio reúne ejercicios y ejemplos orientados al estudio del **cómputo concurrente**, integrando implementaciones en **C** y **C++** que permiten analizar en práctica el funcionamiento de los principales mecanismos de sincronización y control de ejecución paralela.

---
## 🎯 Objetivo del Proyecto

Este repositorio tiene como finalidad servir como base de estudio para analizar el funcionamiento de la concurrencia. A través de implementaciones en C y C++, se busca comprender cómo se coordinan los hilos, cómo se protegen los recursos compartidos y qué técnicas permiten controlar el flujo de ejecución en ambientes paralelos.

---

## 📂 Estructura del Repositorio

```
Cómputo Concurrente/
│
├── CarreraRanitas-PT/
├── Ejercicios/
├── LineaDeProduccion-PT/
├── multiplicacionMatriz-R/
└── README.md
```

A continuación se describe el propósito de cada módulo:

---

### 📁 Ejercicios/
Conjunto de programas prácticos enfocados en los mecanismos fundamentales de concurrencia:

- Hilos  
- Mutex  
- Variables de condición  
- Semáforos  
- Barreras de sincronización  

---

### 📁 CarreraRanitas-PT/
Simulación de una carrera en la que múltiples hilos compiten paralelamente.  
Permite estudiar:

- Condiciones de carrera  
- Sincronización entre hilos  
- Comportamiento no determinista de la ejecución  

---

### 📁 LineaDeProduccion-PT/
Simulación de una línea de producción paralela que incorpora:

- Procesos organizados por etapas  
- Sincronización entre módulos  
- Control de recursos compartidos  
- Interdependencia productor–consumidor  

---

### 📁 multiplicacionMatriz-R/
Implementación orientada a operaciones matemáticas paralelas.  
Refuerza conceptos de:

- División de carga entre hilos  
- Optimización computacional  
- Comparación entre ejecución secuencial vs concurrente  

---

## 🛠️ Tecnologías Empleadas

- C con `<pthread.h>`  
- C con `<semaphore.h>`  
- C++ con `<thread>`, `<mutex>`, `<condition_variable>`, `<semaphore>`, `<barrier>`  
- GCC / G++ con soporte POSIX y C++20  

---

## ▶️ Compilación y Ejecución

### C:
```bash
gcc archivo.c -o programa -lpthread
./programa
```

### C++:
```bash
g++ archivo.cpp -o programa -lpthread -std=c++20
./programa
```

---

## 🤝 Contribuciones

Las contribuciones son bienvenidas. Pueden realizarse mediante *issues* o *pull requests*.

---

## 📝 Licencia

Proyecto con fines académicos y de estudio. Uso libre para aprendizaje y referencia.

---
