/*
This program will numerically compute the integral of
                  4/(1+x*x)
from 0 to 1.
History: Written by Tim Mattson, 11/99.
*/

#include <omp.h>
#include <stdio.h>
static long num_steps = 100000000;
double step;


void main() {
    int i;
    double x, pi, sum = 0.0;
    double start_time, run_time;

    step = 1.0 / (double)num_steps;

    start_time = omp_get_wtime();
    #pragma omp parallel
    {
    	#pragma omp for reduction(+:sum) private(x)  //Specifies that sum is the subject of a reduction operation at the end of the parallel region
    	for (i = 1; i <= num_steps; i++) {           //pecifies that each thread should have its own instance of sum
             x = (i - 0.5) * step;
             sum = sum + 4.0 / (1.0 + x * x);
    	}
    }
    pi = step * sum;
    run_time = omp_get_wtime() - start_time;
    printf("pi with %ld steps is %lf in %lf seconds\n", num_steps, pi, run_time);
}
