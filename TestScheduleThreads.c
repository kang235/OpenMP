#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 4000

void doWork(int t) {
	sleep(t);
}

int* initWork(int n) {
	int i;
	int* wA = (int *)malloc(sizeof(int)*n);
	for (i = 0; i < n; i++) {
		wA[i] = (int)rand() % 2 * i / (n / 10);
	}
	return wA;
}

void omp_scheduling(const int *w)
{
	int i;
	double start = omp_get_wtime();
	
#pragma omp parallel for schedule(dynamic) private(i)
		for (i = 0; i < ARRAY_SIZE; ++i) {
			//printf("Doing work %d = %d\n", i, w[i]);
			doWork(w[i]);
		}

	double end = omp_get_wtime();
	printf("Time for schedule(dynamic) = %.16g\n",end - start);
}

void omp_scheduling_4X_threads(const int *w)
{
	int i;
	int np = omp_get_num_procs(); //by default, thread num is proc num

	double start = omp_get_wtime();

#pragma omp parallel for schedule(dynamic) private(i) num_threads(np*4)
	for (i = 0; i < ARRAY_SIZE; ++i) {
		//printf("Doing work %d = %d\n", i, w[i]);
		doWork(w[i]);
	}

	double end = omp_get_wtime();
	printf("Time for schedule(dynamic) 4X threads = %.16g\n", end - start);
}

int main(int argc, char *argv[]) {
	int *w = initWork(ARRAY_SIZE);

	omp_scheduling(w);
	omp_scheduling_4X_threads(w);

	free(w);
}

