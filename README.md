# OpenMP Assignments

A collection of parallel programming assignments demonstrating various OpenMP concepts including task parallelism, data race prevention, numerical integration, and matrix operations.

## Requirements

- **Compiler:** GCC with OpenMP support (version 4.2 or higher)
- **Compile Flag:** `-fopenmp`
- **OS:** Linux/Ubuntu or Windows with WSL
- **Optional:** `-lm` flag for math library (Assignment 3)

## Compilation Instructions

All programs require the `-fopenmp` flag for OpenMP support.


## Assignments Overview

### Assignment 1: Task Parallelism
- Creates 10 tasks distributed across 4 and 8 threads
- Uses `omp_set_num_threads()` to control thread count
- Demonstrates dynamic task scheduling with `taskwait` synchronization

### Assignment 2: Reduction Operations
- Sums 1,000,000 array elements
- Compares correct implementation (with reduction) vs. data race scenario (without reduction)
- Shows thread distribution and race condition inconsistencies

### Assignment 3: PI Calculation
- Computes PI using 100 million integration steps
- Compares two synchronization methods: reduction (fast) and critical sections (slower)
- Tests performance with 1, 2, 4, and 8 threads
- Achieves ~15 decimal places of accuracy

### Assignment 4: Matrix Operations
- Multiplies 1000×1000 matrix with 1000-element vector
- Compares serial vs. parallel execution
- Benchmarks speedup with varying thread counts (1, 2, 4, 8)
- Demonstrates row-wise parallelization strategy

## Performance Analysis

Each assignment includes timing comparisons demonstrating:
- **Speedup:** Performance gain from parallelization
- **Thread scaling:** How performance changes with different thread counts
- **Synchronization overhead:** Impact of different synchronization methods

Expected performance improvements:
- Assignment 3: 3-4x speedup with 4 threads using reduction
- Assignment 4: 2-3x speedup with 4 threads for matrix operations

## Learning Outcomes

These assignments cover essential OpenMP concepts:
1. **Task Parallelism:** Dynamic task creation and management
2. **Data Sharing:** Understanding shared vs. private variables
3. **Synchronization:** Reduction clauses, critical sections, and barriers
4. **Performance Tuning:** Thread count optimization and load balancing
5. **Race Conditions:** Identifying and preventing parallel programming pitfalls

## Notes

- Assignment 3 requires the math library (`-lm` flag)
- Thread distribution may vary based on system architecture and load
- Results are reproducible with fixed random seed (Assignment 4)
- All timing measurements use `omp_get_wtime()` for accuracy

## 🔗 Related Concepts

- OpenMP API specification
- Parallel algorithm design patterns
- Cache coherency and false sharing
- Amdahl's Law and parallel efficiency

## License
This project is created for educational purposes as part of CDAC ACC HPC coursework.

### ⭐ If you found this helpful, please star this repository!


