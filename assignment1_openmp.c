#include <stdio.h>
#include <omp.h>

int main() {
    printf("=== Testing with omp_set_num_threads() ===\n");
    
    omp_set_num_threads(4);
    
    #pragma omp parallel
    {
        #pragma omp single
        {
            printf("Creating 10 tasks with %d threads\n\n", omp_get_num_threads());
            
            for (int i = 0; i < 10; i++) {
                #pragma omp task
                {
                    printf("Task %d executed by thread %d\n", i, omp_get_thread_num());
                }
            }
            
            
            #pragma omp taskwait
        }
    }
    
    printf("\n=== Now testing with different thread count (8) ===\n");
    omp_set_num_threads(8);
    
    #pragma omp parallel
    {
        #pragma omp single
        {
            printf("Creating 10 tasks with %d threads\n\n", omp_get_num_threads());
            
            for (int i = 0; i < 10; i++) {
                #pragma omp task
                {
                    printf("Task %d executed by thread %d\n", i, omp_get_thread_num());
                }
            }
            
            #pragma omp taskwait
        }
    }
    
    return 0;
}
