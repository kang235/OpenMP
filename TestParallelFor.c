#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define LOOP_NUM 10000

int omp_parallel_and_for()
{
	int i, tid, counter = 0;

	int nt = omp_get_num_procs();

	int *counters = (int*)calloc(nt, sizeof(int));
	if (counters == NULL) exit(-1);

#pragma omp parallel private(i, tid)
	{
		tid = omp_get_thread_num();
		for (i = 0; i < LOOP_NUM; ++i)
		{
			counters[tid]++;
		}
	}

	for (i = 0; i < nt; ++i)
	{
		counter += counters[i];
	}

	return counter;
}

int omp_parallel_for()
{
	int i, tid, counter = 0;

	int nt = omp_get_num_procs();

	int *counters = (int*)calloc(nt, sizeof(int));
	if (counters == NULL) exit(-1);

#pragma omp parallel for private(i, tid)
	for (i = 0; i < LOOP_NUM; ++i)
	{
#pragma omp critical 
		{
			tid = omp_get_thread_num();
			counters[tid]++;
		}
	}

	for (i = 0; i < nt; ++i)
	{
		counter += counters[i];
	}

	return counter;
}

int main(int argc, char *argv[]) {
	printf("OMP parallel and for %d\n", omp_parallel_and_for());
	printf("OMP parallel for %d\n", omp_parallel_for());
}

