#include "benchmarking.h"

void benchmark(double* time) {
    if (*time == 0.0) {
        *time = (double)clock() / CLOCKS_PER_SEC;
    } else {
        *time = ((double)clock() / CLOCKS_PER_SEC) - (*time); 
    }
}
