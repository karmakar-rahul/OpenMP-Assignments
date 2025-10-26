//4.  to write a program for Matrix and vector multiplication.

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define ROWS 1000
#define COLS 1000

void initialize_matrix(double **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = (double)(rand() % 10);
        }
    }
}

void initialize_vector(double *vector, int size) {
    for (int i = 0; i < size; i++) {
        vector[i] = (double)(rand() % 10);
    }
}

void print_result(double *result, int size, int num_to_print) {
    printf("Result vector (first %d elements): ", num_to_print);
    for (int i = 0; i < num_to_print && i < size; i++) {
        printf("%.2f ", result[i]);
    }
    printf("\n");
}

int main() {
    // Allocate memory
    double **matrix = (double**)malloc(ROWS * sizeof(double*));
    for (int i = 0; i < ROWS; i++) {
        matrix[i] = (double*)malloc(COLS * sizeof(double));
    }
    
    double *vector = (double*)malloc(COLS * sizeof(double));
    double *result = (double*)malloc(ROWS * sizeof(double));
    
    // Initialize
    srand(42);  // Fixed seed for reproducibility
    initialize_matrix(matrix, ROWS, COLS);
    initialize_vector(vector, COLS);
    
    printf("Matrix-Vector Multiplication using OpenMP\n");
    printf("Matrix size: %d x %d\n", ROWS, COLS);
    printf("Vector size: %d\n\n", COLS);
    
    printf("=== Serial Version ===\n");
    double start_time = omp_get_wtime();
    
    for (int i = 0; i < ROWS; i++) {
        result[i] = 0.0;
        for (int j = 0; j < COLS; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }
    
    double end_time = omp_get_wtime();
    printf("Time: %.4f seconds\n", end_time - start_time);
    print_result(result, ROWS, 10);
    printf("\n");
    
    printf("=== Parallel Version (with reduction) ===\n");
    omp_set_num_threads(4);
    
    start_time = omp_get_wtime();
    
    #pragma omp parallel for
    for (int i = 0; i < ROWS; i++) {
        double sum = 0.0;
        for (int j = 0; j < COLS; j++) {
            sum += matrix[i][j] * vector[j];
        }
        result[i] = sum;
    }
    
    end_time = omp_get_wtime();
    printf("Threads: %d\n", omp_get_num_threads());
    printf("Time: %.4f seconds\n", end_time - start_time);
    print_result(result, ROWS, 10);
    printf("\n");
    
    printf("=== Thread Distribution (first 20 rows) ===\n");
    
    #pragma omp parallel for
    for (int i = 0; i < 20; i++) {
        #pragma omp critical
        printf("Thread %d computing row %d\n", omp_get_thread_num(), i);
    }
    
    printf("\n");
    
    printf("=== Performance with Different Thread Counts ===\n");
    
    for (int threads = 1; threads <= 8; threads *= 2) {
        omp_set_num_threads(threads);
        
        start_time = omp_get_wtime();
        
        #pragma omp parallel for
        for (int i = 0; i < ROWS; i++) {
            double sum = 0.0;
            for (int j = 0; j < COLS; j++) {
                sum += matrix[i][j] * vector[j];
            }
            result[i] = sum;
        }
        
        end_time = omp_get_wtime();
        
        printf("Threads: %d, Time: %.4f seconds, Speedup: %.2fx\n", 
               threads, end_time - start_time, 
               0.1 / (end_time - start_time));  
        // Approximate speedup
    }
    
    // Free memory
    for (int i = 0; i < ROWS; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(vector);
    free(result);
    
    return 0;
}
