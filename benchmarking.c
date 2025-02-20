#include "benchmarking.h"


double benchmark(double* time){
    if (*time == 0.0){
        return (double)clock();
    } else {
        return ((double)clock() / CLOCKS_PER_SEC) - (*time);
    }
}
