#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define ARRAY_SIZE 10000

void doWork(int t) {
	usleep(t);
}

int* initWork(int n) {
	int i;
	int* wA = (int *)malloc(sizeof(int)*n);
	for (i = 0; i < n; i++) {
		wA[i] = (int)rand() % 2 * i / (n / 10);
	}
	return wA;
}

void seq_for_loop(const int *w)
{
	int i;
	double start = omp_get_wtime();

	for (i = 0; i < ARRAY_SIZE; ++i)
	{
		doWork(w[i]);
	}

	double end = omp_get_wtime();
	printf("Time with sequential for loop = %.16g\n", end - start);
}

void omp_parallel_sections(const int *w)
{
	int num_proc = omp_get_num_procs();
	int num_work_each_thread = ARRAY_SIZE / num_proc;
	assert(ARRAY_SIZE % num_proc == 0);

	double start = omp_get_wtime();

#pragma omp parallel sections
	{
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
#pragma omp section
	{
		int i;
		int tid = omp_get_thread_num();
		int range = (tid + 1) * num_work_each_thread;
		for (i = tid * num_work_each_thread; i < range; ++i)
		{
			doWork(w[i]);
		}
	}
	}

	double end = omp_get_wtime();
	printf("Time with parallel section loops = %.16g\n", end - start);
}

int main(int argc, char *argv[]) {
	int *w = initWork(ARRAY_SIZE);

	seq_for_loop(w);
	omp_parallel_sections(w);

	free(w);
}

