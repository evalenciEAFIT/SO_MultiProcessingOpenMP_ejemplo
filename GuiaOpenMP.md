# Guía de OpenMP: Comandos y Usos

## ¿Qué es OpenMP?

OpenMP (Open Multi-Processing) es una API que soporta la programación multiproceso de memoria compartida en múltiples plataformas. Permite añadir concurrencia a programas escritos en C, C++ y Fortran de manera sencilla y portable.

## Contexto y Usos de OpenMP

OpenMP se utiliza principalmente en situaciones donde se requiere paralelismo de datos o de tareas en sistemas de memoria compartida. Algunos contextos comunes incluyen:

- Computación científica y simulaciones
- Procesamiento de imágenes y video
- Análisis de datos a gran escala
- Algoritmos de búsqueda y ordenamiento
- Operaciones matriciales y vectoriales

## Comandos Más Usados en OpenMP

### 1. Directiva Parallel

Crea un equipo de hilos para ejecutar un bloque de código en paralelo.

```c
#pragma omp parallel
{
    // Código ejecutado por múltiples hilos
}
```

**Ejemplo:**

```c
#pragma omp parallel
{
    printf("Hola desde el hilo %d\n", omp_get_thread_num());
}
```

### 2. Directiva For

Distribuye las iteraciones de un bucle entre los hilos disponibles.

```c
#pragma omp parallel for
for (int i = 0; i < n; i++) {
    // Iteraciones ejecutadas en paralelo
}
```

**Ejemplo:**

```c
#pragma omp parallel for
for (int i = 0; i < 1000; i++) {
    result[i] = heavy_computation(i);
}
```

### 3. Cláusula Private

Declara variables como privadas para cada hilo.

```c
#pragma omp parallel for private(x)
for (int i = 0; i < n; i++) {
    // x es privada para cada hilo
}
```

**Ejemplo:**

```c
int sum = 0;
#pragma omp parallel for private(temp)
for (int i = 0; i < n; i++) {
    int temp = array[i] * 2;
    #pragma omp critical
    sum += temp;
}
```

### 4. Cláusula Reduction

Combina valores de variables privadas en una única variable compartida.

```c
#pragma omp parallel for reduction(+:sum)
for (int i = 0; i < n; i++) {
    sum += array[i];
}
```

**Ejemplo:**

```c
int max_val = 0;
#pragma omp parallel for reduction(max:max_val)
for (int i = 0; i < n; i++) {
    if (array[i] > max_val) max_val = array[i];
}
```

### 5. Directiva Critical

Define una sección crítica que solo puede ser ejecutada por un hilo a la vez.

```c
#pragma omp critical
{
    // Código ejecutado por un solo hilo a la vez
}
```

**Ejemplo:**

```c
#pragma omp parallel
{
    #pragma omp critical
    {
        shared_resource++;
        printf("Recurso actualizado por el hilo %d\n", omp_get_thread_num());
    }
}
```

## Conclusión

OpenMP proporciona una forma sencilla y eficaz de paralelizar código en sistemas de memoria compartida. Su uso adecuado puede llevar a mejoras significativas en el rendimiento de aplicaciones que manejan grandes cantidades de datos o cálculos intensivos. Sin embargo, es importante entender los conceptos de paralelismo y las características específicas de OpenMP para utilizarlo de manera efectiva y evitar problemas como condiciones de carrera o sobrecarga excesiva.