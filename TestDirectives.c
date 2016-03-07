#include <omp.h>
#include <stdio.h>

void omp_critical()
{
	int tid;

#pragma omp parallel
	{
		printf("Test Directives Critical\n");
#pragma omp critical
		{
			/* Obtain thread number */
			tid = omp_get_thread_num();

			printf("tid: %d\n", tid);
		}
	}  /* All threads join master thread and disband */

}

void omp_master()
{
	int tid;

#pragma omp parallel private(tid)
	{
		printf("Test Directives\n");
#pragma omp master 
		{
			/* Obtain thread number */
			tid = omp_get_thread_num();

			printf("tid: %d\n", tid);
		}
	}  /* All threads join master thread and disband */

}

void omp_single()
{
	int tid;

#pragma omp parallel private(tid)
	{
		printf("Test Directives\n");
#pragma omp single 
		{
			/* Obtain thread number */
			tid = omp_get_thread_num();

			printf("tid: %d\n", tid);
		}
	}  /* All threads join master thread and disband */
}

int main(int argc, char *argv[]) {
	printf("critical: \n");
	omp_critical();
	printf("\nMaster: \n");
	omp_master();
	printf("\nSingle: \n");
	omp_single();
}

