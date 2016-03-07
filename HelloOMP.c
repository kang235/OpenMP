#include <omp.h>
#include <stdio.h>

void print_omp_inf();

int main(int argc, char *argv[]) {
	print_omp_inf();

	return 0;
}

void print_omp_inf()
{
	int nprocs, nthreads, tid;

	/* Fork a team of threads giving them their own copies of variables */
#pragma omp parallel private(nprocs, nthreads, tid)
	{
		/* Obtain thread number */
		tid = omp_get_thread_num();

		/* Only master thread does this */
		if (tid == 0)
		{
			nprocs = omp_get_num_procs();
			printf("Number of processors = %d\n", nprocs);

			nthreads = omp_get_num_threads();
			printf("Number of threads = %d\n", nthreads);
		}

#pragma omp single
		{
			/* Obtain thread number */
			tid = omp_get_thread_num();

			printf("Execute single from thread = %d\n", tid);
		}

#pragma omp master
		{
			/* Obtain thread number */
			tid = omp_get_thread_num();

			printf("Execute master from thread = %d\n", tid);
		}

		printf("Hello World from thread = %d\n", tid);

	} /* All threads join master thread and disband */

	printf("\n");
}