//2. To write a parallel program to find sum of an array	
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define ARRAY_SIZE 1000000

int main() {
    int *array = (int*)malloc(ARRAY_SIZE * sizeof(int));
    long long sum;
    
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = i + 1;  // 1, 2, 3, ..., 1000000
    }
    
    printf("Array size: %d\n", ARRAY_SIZE);
    printf("Expected sum: %lld\n\n", (long long)ARRAY_SIZE * (ARRAY_SIZE + 1) / 2);
    
    printf("=== WITH REDUCTION (Correct) ===\n");
    omp_set_num_threads(4);
    sum = 0;
    
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sum += array[i];
        

        if (i < 20) {
            #pragma omp critical
            printf("Thread %d handling iteration %d\n", omp_get_thread_num(), i);
        }
    }
    
    printf("Sum with reduction: %lld\n\n", sum);
    
    printf("=== WITHOUT REDUCTION (Data Race!) ===\n");
    printf("Running 5 times to show inconsistent results:\n\n");
    
    for (int run = 1; run <= 5; run++) {
        sum = 0;
        
        #pragma omp parallel for
        for (int i = 0; i < ARRAY_SIZE; i++) {
            sum += array[i];  
        }
        
        printf("Run %d - Sum without reduction: %lld ", run, sum);
        if (sum == (long long)ARRAY_SIZE * (ARRAY_SIZE + 1) / 2) {
            printf("(Correct by chance!)\n");
        } else {
            printf("(WRONG - Data race!)\n");
        }
    }
    
    printf("\n=== Showing Thread Distribution ===\n");
    omp_set_num_threads(4);
    
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < 40; i++) {
        printf("Thread %d handles iteration %d\n", omp_get_thread_num(), i);
    }
    
    free(array);
    return 0;
}
