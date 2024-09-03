#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#ifdef _OPENMP
#include <omp.h>
#endif

const int N = 1000; // Tamaño de la matriz

// Función para asignar memoria para una matriz
double** allocateMatrix(int rows, int cols) {
    double** matrix = new double*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new double[cols];
    }
    return matrix;
}

// Función para liberar la memoria de una matriz
void freeMatrix(double** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

// Inicializa una matriz con valores aleatorios
void initialize_matrix(double** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() / (double)RAND_MAX;
        }
    }
}

// Multiplicación de matrices serial
void multiply_matrices_serial(double** A, double** B, double** C, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            C[i][j] = 0.0;
            for (int k = 0; k < cols; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Multiplicación de matrices paralela usando OpenMP
void multiply_matrices_parallel(double** A, double** B, double** C, int rows, int cols) {
    #pragma omp parallel for
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            C[i][j] = 0.0;
            for (int k = 0; k < cols; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Función para medir el tiempo de ejecución
double get_execution_time(void (*func)(double**, double**, double**, int, int), 
                          double** A, double** B, double** C, int rows, int cols) {
    auto start = std::chrono::high_resolution_clock::now();
    func(A, B, C, rows, cols);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    return diff.count();
}

int main() {
    srand(time(NULL));

    double **A, **B, **C;

    try {
        A = allocateMatrix(N, N);
        B = allocateMatrix(N, N);
        C = allocateMatrix(N, N);
    } catch (std::bad_alloc& ba) {
        std::cerr << "Error: no se pudo asignar memoria para las matrices. " << ba.what() << std::endl;
        return 1;
    }

    initialize_matrix(A, N, N);
    initialize_matrix(B, N, N);

    std::cout << "Multiplicación de matrices " << N << "x" << N << std::endl;

    double serial_time = get_execution_time(multiply_matrices_serial, A, B, C, N, N);
    std::cout << "Tiempo de ejecución (serial): " << serial_time << " segundos" << std::endl;

    double parallel_time = get_execution_time(multiply_matrices_parallel, A, B, C, N, N);
    std::cout << "Tiempo de ejecución (paralelo): " << parallel_time << " segundos" << std::endl;

    double speedup = serial_time / parallel_time;
    std::cout << "Acelaración: " << speedup << "x" << std::endl;

    // Liberar memoria
    freeMatrix(A, N);
    freeMatrix(B, N);
    freeMatrix(C, N);

    return 0;
}