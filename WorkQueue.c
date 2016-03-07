#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 1000000

typedef struct Q {
   int* q;
   int pos;
   int size;
} Q;

struct Q* initQ(int n) {
   //int i;
   struct Q *newQ = (struct Q *) malloc(sizeof(Q));   
   newQ->q = (int*) malloc(sizeof(int)*n);
   if (newQ->q == NULL) { printf("Cannot malloc memory!\n"); return NULL; }
   newQ->pos = -1;
   newQ->size = n-1;

   return newQ;
}

void putWork(struct Q* workQ) {
   if (workQ->pos < (workQ->size)) {
      workQ->pos++;
      workQ->q[workQ->pos] = (int) (rand( )%2*(workQ->pos/1000));
   } else printf("ERROR: attempt to add Q element%d\n", workQ->pos+1);
}

int getWork(struct Q* workQ) {
   if (workQ->pos > -1) {
      int w = workQ->q[workQ->pos];
      workQ->pos--;
      return w;
   } else printf("ERROR: attempt to get work from empty Q%d\n", workQ->pos);

   return -1;
}

void finalizeQ(struct Q* workQ)
{
	free(workQ->q);
	free(workQ);
}

void seq_loop(Q *queue)
{
	int i;
	for (i = 0; i < ARRAY_SIZE; ++i)
	{
		putWork(queue);
	}

	double start = omp_get_wtime();
	for (i = 0; i < ARRAY_SIZE; ++i)
	{
		int r = getWork(queue);
		//printf("Sequential %d\n", getWork(queue));
	}
	double end = omp_get_wtime();
	printf("Time with sequential for loop = %.16g\n", end - start);
}

void par_loop(Q *queue)
{
	omp_lock_t lck;
	omp_init_lock(&lck);
	
	int i;
	for (i = 0; i < ARRAY_SIZE; ++i)
	{
		putWork(queue);
	}

	double start = omp_get_wtime();

#pragma omp parallel for schedule(dynamic) private(i)
	for (i = 0; i < ARRAY_SIZE; ++i)
	{
		omp_set_lock(&lck);
		int r = getWork(queue);
		omp_unset_lock(&lck);
	}
	omp_destroy_lock(&lck);

	double end = omp_get_wtime();
	printf("Time with parallel for loop = %.16g\n", end - start);
}

int main(int argc, char *argv[]) 
{
	Q *queue = initQ(ARRAY_SIZE);

	seq_loop(queue);
	par_loop(queue);

	finalizeQ(queue);
}
