# 📌 Línea de Producción Concurrente ⚙️

Este programa implementa un proceso de ensamblaje concurrente utilizando múltiples mecanismos de sincronización de hilos en C: barreras, semáforos, mutex y variables de condición. Simula una línea de producción donde los productos deben pasar por tres fases claramente definidas: **🔪 Cortar → 🛠️ Soldar → 🎨 Pintar**.

---

## 🔒 Uso de mecanismos de sincronización

### 🚦 Semáforos:
Utilizados como contadores para indicar el estado del producto en cada etapa. Un valor en cero bloquea el hilo que ejecuta `sem_wait()` hasta que otro hilo realice `sem_post()`.

### 🔐 Mutex:
Utilizado para proteger las secciones críticas, especialmente la salida estándar (`printf`), evitando condiciones de carrera y mensajes mezclados.

### 🚧 Barreras:
Utilizada (`pthread_barrier_wait`) para asegurar que ningún hilo pase al siguiente producto hasta que todos los hilos (cortadores, soldadores y pintores) hayan terminado el actual. Esto garantiza sincronización global al final de cada iteración.

### 📢 Variables de condición:
Utilizadas para notificaciones puntuales (`pthread_cond_signal`). Aunque no son estrictamente necesarias (ya que están sincronizadas mediante semáforos), se mantienen para conservar la estructura original del programa.

---

## 🔄 Flujo de Trabajo del Programa

El ensamblaje de cada producto sigue estrictamente el orden:

### 🔪 Fase de Cortado
- Los cortadores esperan (`sem_wait(&productos_pintados)`) hasta que la etapa previa (pintura) haya finalizado.
- Realizan su trabajo (protegido con mutex) y al finalizar incrementan el contador de productos cortados (`sem_post(&productos_cortados)`).
- Notifican a los soldadores usando variables de condición (`pthread_cond_signal(&puede_soldar)`).

### 🛠️ Fase de Soldadura
- Los soldadores esperan (`sem_wait(&productos_cortados)`) hasta que un producto haya sido cortado.
- Realizan su trabajo (protegido con mutex) e incrementan el contador de productos soldados (`sem_post(&productos_soldados)`).
- Notifican a los pintores (`pthread_cond_signal(&puede_pintar)`).

### 🎨 Fase de Pintura
- Los pintores esperan (`sem_wait(&productos_soldados)`) hasta que un producto esté soldado.
- Realizan su tarea (protegido con mutex), incrementan el contador de productos pintados (`sem_post(&productos_pintados)`), habilitando a los cortadores para iniciar el siguiente ciclo.
- Notifican nuevamente a los cortadores (`pthread_cond_signal(&puede_cortar)`).

🔗 **Sincronización Global:** Al final de cada iteración (producto), todos los hilos se sincronizan mediante una barrera (`pthread_barrier_wait`), asegurando que ninguna etapa del siguiente producto comience hasta que todos los hilos hayan finalizado el actual.

---

## 🚀 Compilación y Ejecución

Compilar:
```bash
g++ -o build/app app.c
```

Ejecutar (ejemplo con 2 cortadores, 2 soldadores, 2 pintores):
```bash
./build/app 2 2 2
```

---

## ⚠️ Posibles Problemas
- **Deadlock:** si algún hilo se queda bloqueado indefinidamente esperando en un semáforo que no se incrementa.
- **Starvation:** posibilidad remota si no existe un balance adecuado en el número de hilos entre etapas.

---

## 📈 Posibles Mejoras
- Simplificar eliminando variables de condición redundantes.
- Optimizar para evitar bloqueos innecesarios (uso eficiente del mutex).
- Realizar análisis de escalabilidad para grandes cantidades de hilos.

---

## 🤝 Cómo contribuir

¡Si deseas contribuir a este proyecto, siéntete libre de hacer un fork y enviar un pull request! Aquí algunas sugerencias:

- Mejorar la claridad del código.
- Optimizar el rendimiento de los mecanismos de sincronización.
- Experimentar con distintas técnicas y proponer nuevas características.

---

🎉 **Gracias por leer y contribuir. ¡Diviértete ensamblando productos!** 🚀🛠️🎨