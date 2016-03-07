#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <assert.h>

#define THREADNUM 64 
//in the tree traverse, levels below PARLVL will be in sequential
#define PARLVL 5
#define TESTTIMES 10

typedef struct node {
	float val;
	int lvl;
	struct node *left, *right;
} Node, *NodePtr;

NodePtr create_tree_seq(const int maxlvl, int curlvl, const int nodesnum, int *count)
{
	if (curlvl >= maxlvl)
	{
		return NULL;
	}
	else
	{
		if ((*count) >= nodesnum)
		{
			return NULL;
		}

		NodePtr pnode = (NodePtr)malloc(sizeof(Node));
		if (!pnode) { perror("Failed to malloc memory!\n"); return NULL; }

		pnode->val = (float)rand() / RAND_MAX; //rand a 0-1 number
		pnode->lvl = curlvl;

		(*count)++;
		curlvl++;
		//printf("%f\n", pnode->val);

		pnode->left = create_tree_seq(maxlvl, curlvl, nodesnum, count);
		pnode->right = create_tree_seq(maxlvl, curlvl, nodesnum, count);

		return pnode;
	}
}

void traverse_tree_seq(const NodePtr node, int *count)
{
	if (node->left) traverse_tree_seq(node->left, count);
	if (node->right) traverse_tree_seq(node->right, count);

	//printf("reached end\n");
	if (node->val < 0.5)
		(*count)++;
}

int traverse_par(const NodePtr node)
{
	//if leaf
	if (!node->left&&!node->right)
	{
		return (node->val < 0.5) ? 1 : 0;
	}

	int count0 = 0, count1 = 0;
	
	//create new tasks when lvl <= predefined value
	if (node->lvl <= PARLVL)
	{
#pragma omp task shared(count0) 
		if (node->left) count0 = traverse_par(node->left);
#pragma omp task shared(count1)
		if (node->right) count1 = traverse_par(node->right);
#pragma omp taskwait
	}
	//use sequential traverse for lvls > predefined value
	else
	{
		if (node->left) count0 = traverse_par(node->left);
		if (node->right) count1 = traverse_par(node->right);
	}

	count0 += count1;

	return (node->val < 0.5) ? count0 + 1 : count0;
}

void traverse_tree_par(const NodePtr node, int *count)
{
	omp_set_num_threads(THREADNUM);
#pragma omp parallel
#pragma omp single
	{
		printf("Number of thread: %d\n", omp_get_num_threads());
		*count = traverse_par(node);
	}
}

//All the maxlvl-1 levels must be full.  
//There might be remaining nodes(leaves) in the final level, which is not full.
NodePtr create_tree_par(const int maxlvl, int curlvl, const int remnum, int *remcount) //,  int *count)
{
	//exceed the lvl
	if (curlvl >= maxlvl)
	{
		return NULL;
	}
	//for the remaining nodes(leaves) in the final level
	else if (curlvl == maxlvl - 1)
	{
		if (*remcount >= remnum)
		{
			return NULL;
		}

		NodePtr pnode = (NodePtr)malloc(sizeof(Node));
		if (!pnode) { perror("Failed to malloc memory!\n"); exit(-1); }

		pnode->val = (float)rand() / RAND_MAX; //rand a 0-1 number
		pnode->lvl = curlvl;
		pnode->left = NULL;
		pnode->right = NULL;
#pragma omp critical
		{
			if (*remcount < remnum)
			{
				(*remcount)++;
				//(*count)++;
			}
			else
			{	
				curlvl = maxlvl;  //reach the number of nodes we need
			}
		}

		return pnode;
	}
	//all the levels above should be full (all have left and right)
	else
	{
		NodePtr pnode = (NodePtr)malloc(sizeof(Node));
		if (!pnode) { perror("Failed to malloc memory!\n"); exit(-1); }

		pnode->val = (float)rand() / RAND_MAX; //rand a 0-1 number
		pnode->lvl = curlvl;
		/*
		#pragma omp critical
		{
		(*count)++;
		}
		*/
		curlvl++;
		//printf("Node val: %f\n", pnode->val);

		//create new tasks before reaching a predefined value
		if (curlvl <= PARLVL)
		{
#pragma omp task
			pnode->left = create_tree_par(maxlvl, curlvl, remnum, remcount); //, count);
#pragma omp task
			pnode->right = create_tree_par(maxlvl, curlvl, remnum, remcount); //, count);
#pragma omp taskwait
		}
		//use sequential traverse
		else
		{
			pnode->left = create_tree_par(maxlvl, curlvl, remnum, remcount); //, count);
			pnode->right = create_tree_par(maxlvl, curlvl, remnum, remcount); //, count);

		}

		return pnode;
	}
}

NodePtr init_tree_par(const int maxlvl, int curlvl, const int remnum, int *remcount) //,  int *count)
{
	NodePtr pnode;

#pragma omp parallel
#pragma omp single
	{
		//printf("Number of thread: %d\n", omp_get_num_threads());
		pnode = create_tree_par(maxlvl, curlvl, remnum, remcount); //, count);
	}

	return pnode;
}

void destroy_tree(NodePtr node)
{
	if (node->left) destroy_tree(node->left);
	if (node->right) destroy_tree(node->right);

	free(node);
}

//Get two values based on the number of nodes:
//fulllvl: the number of levels that are full
//remainer: there might be some remaining nodes in the final level
//			that cannot form a full level. The number of these nodes.
void get_tree_info(int nodenum, int * fulllvl, int * remainer)
{
	assert(nodenum > 0);
	int n = nodenum + 1;
	*fulllvl = -1;

	do
	{
		n /= 2;
		(*fulllvl)++;
	} while (n != 0);

	*remainer = (nodenum + 1) % (int)pow(2, *fulllvl);
}

int main(int args, char *argv[])
{
	int nodesnum = 0x400000;
	//int nodesnum = 15;
	double start, end;

	int fulllvl, remainer;
	get_tree_info(nodesnum, &fulllvl, &remainer);

	/*	
	printf("fulllvl: %d\n", fulllvl);
	printf("remainer: %d\n", remainer);
	*/
	/*	
	int counter0 = 0;
	NodePtr tree0 = create_tree_seq( fulllvl + 1, 0, nodesnum, &counter0);
	printf("Node count seq: %d\n", counter0);
	
	destroy_tree(tree0);
	*/

	//int counter2 = 0;	
	int counter3 = 0;
	start = omp_get_wtime();
	NodePtr tree1 = init_tree_par(fulllvl + 1, 0, remainer, &counter3); //, &counter2);
	end = omp_get_wtime();
	printf("Tree created with %d nodes in parallel\n", nodesnum);
	//printf("Node count par: %d \n", counter2);
	printf("Time used: %.16g\n", end - start);
	
	int i, counter4, counter5;
	double seqtime = 0, partime = 0;

	for (i = 0; i < TESTTIMES; ++i)
	{
		printf("\nTest %d/%d\n", i + 1, TESTTIMES);
		printf("In sequential:\n");
		counter4 = 0;
		start = omp_get_wtime();
		traverse_tree_seq(tree1, &counter4);
		end = omp_get_wtime();

		printf("Node count with value less than 0.5: %d\n", counter4);
		seqtime += end - start;
		printf("Time used in sequential tree traverse: %.16g\n", end - start);

		printf("In parallel:\n");
		counter5 = 0;
		start = omp_get_wtime();
		traverse_tree_par(tree1, &counter5);
		end = omp_get_wtime();

		printf("Node count with value less than 0.5: %d\n", counter5);
		partime += end - start;
		printf("Time used in parallel tree traverse: %.16g\n", end - start);
	}

	printf("\nIn average, sequential tree traverse time: %lf\n", seqtime / TESTTIMES);
	printf("              parallel tree traverse time: %lf\n", partime / TESTTIMES);
	destroy_tree(tree1);
	return 0;
}
