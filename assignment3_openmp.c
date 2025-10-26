#include <stdio.h>
#include <omp.h>

#define NUM_STEPS 100000000  // 100 million steps

int main() {
    int num_steps = NUM_STEPS;
    double step = 1.0 / (double)num_steps;
    double pi, sum = 0.0;
    double start_time, end_time;
    
    printf("Computing PI using numerical integration\n");
    printf("Number of steps: %d\n\n", num_steps);
    
    printf("=== Method 1: Using reduction ===\n");
    omp_set_num_threads(4);
    
    sum = 0.0;
    start_time = omp_get_wtime();
    
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < num_steps; i++) {
        double x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }
    
    pi = step * sum;
    end_time = omp_get_wtime();
    
    printf("Computed PI = %.15f\n", pi);
    printf("Actual PI   = 3.141592653589793\n");
    printf("Error       = %.15f\n", pi - 3.141592653589793);
    printf("Time taken  = %.4f seconds\n", end_time - start_time);
    printf("Threads used: %d\n\n", omp_get_max_threads());
    
    printf("=== Method 2: Using critical section (slower) ===\n");
    
    sum = 0.0;
    start_time = omp_get_wtime();
    
    #pragma omp parallel
    {
        double local_sum = 0.0;
        
        #pragma omp for
        for (int i = 0; i < num_steps; i++) {
            double x = (i + 0.5) * step;
            local_sum += 4.0 / (1.0 + x * x);
        }
        
        #pragma omp critical
        sum += local_sum;
    }
    
    pi = step * sum;
    end_time = omp_get_wtime();
    
    printf("Computed PI = %.15f\n", pi);
    printf("Time taken  = %.4f seconds\n\n", end_time - start_time);
    
    printf("=== Testing with different thread counts ===\n");
    
    for (int threads = 1; threads <= 8; threads *= 2) {
        omp_set_num_threads(threads);
        sum = 0.0;
        
        start_time = omp_get_wtime();
        
        #pragma omp parallel for reduction(+:sum)
        for (int i = 0; i < num_steps; i++) {
            double x = (i + 0.5) * step;
            sum += 4.0 / (1.0 + x * x);
        }
        
        pi = step * sum;
        end_time = omp_get_wtime();
        
        printf("Threads: %d, PI = %.10f, Time = %.4f seconds\n", 
               threads, pi, end_time - start_time);
    }
    
    return 0;
}
