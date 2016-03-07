#include <omp.h>
#include <stdio.h>

int f1()
{
	int i, tid, sum = 0;
	for (i = 0; i < 10; ++i)
	{
		sum += i;
#pragma omp critical 
		{
			tid = omp_get_thread_num();
			printf("In f1() with thread %d\n", tid);
		}
	}

	return sum;
}

int f2()
{
	int i, tid, sum = 0;
	for (i = 0; i < 10; ++i)
	{
		sum -= i;
#pragma omp critical 
		{
			tid = omp_get_thread_num();
			printf("In f2() with thread %d\n", tid);
		}
	}

	return sum;
}

void omp_section()
{
#pragma omp parallel sections
{
#pragma omp section
{
	printf("Result of f1(): %d\n", f1());
}
#pragma omp section
{
	printf("Result of f2(): %d\n", f2());
}
}
}

int main(int argc, char *argv[]) {
	omp_section();
}

