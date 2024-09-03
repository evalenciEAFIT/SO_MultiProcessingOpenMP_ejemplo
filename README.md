# Multiplicación de Matrices con OpenMP

Este proyecto demuestra la multiplicación de matrices utilizando OpenMP para paralelización en C++, con énfasis en el manejo eficiente de la memoria y el rendimiento.

## Contenido

1. [Requisitos del sistema](#requisitos-del-sistema)
2. [Instalación de librerías](#instalación-de-librerías)
3. [Multiplicación de matrices](#multiplicación-de-matrices)
4. [Estructura del código](#estructura-del-código)
5. [OpenMP](#openmp)
6. [Uso de OpenMP en este proyecto](#uso-de-openmp-en-este-proyecto)
7. [Compilación y ejecución](#compilación-y-ejecución)
8. [Optimizaciones y consideraciones](#optimizaciones-y-consideraciones)

## Requisitos del sistema

- Compilador C++ que soporte C++11 o superior
- OpenMP (generalmente incluido en compiladores modernos)
- Suficiente memoria RAM para manejar matrices grandes

## Instalación de librerías

OpenMP generalmente está incluido en compiladores modernos. Si necesita instalarlo:

### Linux (Ubuntu/Debian)
```bash
sudo apt-get update
sudo apt-get install libomp-dev
```

### macOS (usando Homebrew)
```bash
brew install libomp
```

### Windows
Para Visual Studio, OpenMP ya está incluido. Para MinGW:
```
mingw-get install mingw32-pthreads-w32
```

## Multiplicación de matrices

La multiplicación de matrices C = A × B se define como:

C[i][j] = Σ(A[i][k] * B[k][j]) para k = 0 hasta n-1

donde A es una matriz de dimensiones m×n, B es n×p, y C es m×p.

## Estructura del código

El código fuente (`MultiplicaciónMatrices.cpp`) incluye:

1. Funciones para asignación y liberación de memoria dinámica.
2. Inicialización de matrices con valores aleatorios.
3. Implementaciones serial y paralela de multiplicación de matrices.
4. Medición precisa del tiempo de ejecución.
5. Manejo de errores para asignación de memoria.

## OpenMP

OpenMP (Open Multi-Processing) es una API que soporta programación multiproceso de memoria compartida en múltiples plataformas. Permite añadir concurrencia a los programas en C, C++ y Fortran de manera sencilla y portable.

Características principales:
- Modelo de programación fork-join
- Especificación de regiones paralelas mediante directivas de compilador
- Reparto de trabajo entre hilos
- Sincronización de datos y tareas

## Uso de OpenMP en este proyecto

En este proyecto, OpenMP se utiliza para paralelizar el bucle más externo de la multiplicación de matrices:

```cpp
#pragma omp parallel for
for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
        C[i][j] = 0.0;
        for (int k = 0; k < cols; k++) {
            C[i][j] += A[i][k] * B[k][j];
        }
    }
}
```

Esta configuración ofrece:
1. Buena granularidad: cada hilo procesa filas completas.
2. Minimización de la creación/destrucción de hilos.
3. Mejora en la localidad de caché.

## Compilación y ejecución

1. Compilar:
   ```
   g++ -std=c++11 -fopenmp MultiplicaciónMatrices.cpp -o MultiplicaciónMatrices
   ```

2. Ejecutar:
   ```
   ./MultiplicaciónMatrices
   ```

3. Para especificar el número de hilos:
   ```
   export OMP_NUM_THREADS=4
   ./MultiplicaciónMatrices
   ```

## Optimizaciones y consideraciones

1. **Asignación dinámica de memoria**: El programa utiliza `new` para asignar memoria dinámicamente, permitiendo trabajar con matrices más grandes sin desbordar la pila.

2. **Manejo de errores**: Se implementa un manejo de errores para la asignación de memoria, mejorando la robustez del programa.

3. **Medición precisa del tiempo**: Se utiliza `std::chrono::high_resolution_clock` para una medición más precisa del tiempo de ejecución.

4. **Tamaño de las matrices**: El tamaño de las matrices (N) se puede ajustar en el código fuente. Para matrices muy grandes, asegúrese de tener suficiente memoria RAM.

5. **Rendimiento**: La versión paralela debería mostrar una mejora significativa en sistemas con múltiples núcleos. El speedup puede variar dependiendo del hardware y el tamaño de las matrices.

6. **Optimizaciones adicionales**: Para matrices muy grandes, considere técnicas como el blocking para mejorar la localidad de caché.

Este README proporciona una guía completa para entender, compilar y ejecutar el programa de multiplicación de matrices utilizando OpenMP, con énfasis en el manejo eficiente de la memoria y las consideraciones de rendimiento.
