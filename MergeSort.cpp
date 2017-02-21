#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <omp.h>
#include <tbb/tbb.h>

using namespace tbb;
using namespace std;

void initArray(int *a, int count)
{
	for (int i = 0; i < count; ++i)
		a[i] = rand() % count;
}

void printArray(int *a, int count)
{
	for (int i = 0; i < count; ++i)
		cout << a[i] << " ";
	cout << endl;
}

bool compareArrays(int *a, int *b, int count)
{
	for (int i = 0; i < count; ++i)
		if (a[i] != b[i]) return false;
	return true;
}

void sort_rec(int *a, int *b, int count)
{
	if (count == 1)
		return;

	int half = count >> 1;

	sort_rec(a, b, half);
	sort_rec(a + half, b + half, count - half);

	int n1 = 0;
	int n2 = 0;
	for (int i = 0; i < count; ++i) {
		if (a[n1] <= a[half + n2] && n1 < half || n2 >= count - half) {
			b[i] = a[n1++];
		}
		else if (a[n1] > a[half + n2] && n2 < count - half || n1 >= half) {
			b[i] = a[half + n2++];
		}
	}
	memcpy(a, b, count * sizeof(int));
}

void sort_rec_omp(int *a, int *b, int count, int lvl)
{
	if (count == 1)
		return;

	int half = count >> 1;
	omp_set_nested(1);
	omp_set_num_threads(2);

	bool flag = lvl <= 8 ? true : false;

#pragma omp parallel sections if(flag)
	{
#pragma omp section
	{
		//omp_set_num_threads(2);
		//printf("id = %d \n", omp_get_thread_num());
		sort_rec_omp(a, b, half, ++lvl);
	}
#pragma omp section
	{
		//omp_set_num_threads(2);
		//printf("id = %d \n", omp_get_thread_num());
		sort_rec_omp(a + half, b + half, count - half, ++lvl);
	}
	}

	int n1 = 0;
	int n2 = 0;
	for (int i = 0; i < count; ++i) {
		if (a[n1] <= a[half + n2] && n1 < half || n2 >= count - half) {
			b[i] = a[n1++];
		}
		else if (a[n1] > a[half + n2] && n2 < count - half || n1 >= half) {
			b[i] = a[half + n2++];
		}
	}
	memcpy(a, b, count * sizeof(int));
}

void sort_rec_tbb(int *a, int *b, int count)
{
	if (count == 1)
		return;

	int half = count >> 1;

	tbb::parallel_invoke([=]() {sort_rec(a, b, half);}, [=]() {sort_rec(a + half, b + half, count - half);});

	int n1 = 0;
	int n2 = 0;
	for (int i = 0; i < count; ++i) {
		if (a[n1] <= a[half + n2] && n1 < half || n2 >= count - half) {
			b[i] = a[n1++];
		}
		else if (a[n1] > a[half + n2] && n2 < count - half || n1 >= half) {
			b[i] = a[half + n2++];
		}
	}
	memcpy(a, b, count * sizeof(int));
}

void sort_tbb(int * a, int * b, int count) {
	int stride = 2;

	while ((stride >> 1) < count)
	{
		int half = stride >> 1;
		parallel_for(0, count, stride, [=](size_t i) {
			int n1 = i;
			int n2 = i + half < count ? i + half : count;
			int mid = n2;
			int end = i + stride < count ? i + stride : count;
			int size = (i + stride > count) ? count - i : stride;
			for (int j = 0; j < size; ++j) {
				if ((a[n1] <= a[n2] || n2 >= end) && n1 < mid) {
					b[j + i] = a[n1++];
				}
				else {
					b[j + i] = a[n2++];
				}
			}
			memcpy(a + i, b + i, size * sizeof(int));
		});
		stride = stride << 1;
	}
}

void sort_omp(int * a, int * b, int count) {
	int stride = 2;

	while ((stride >> 1) < count)
	{
		int half = stride >> 1;
#pragma omp parallel for num_threads(256)
		for (int i = 0; i < count; i += stride) {
			int n1 = i;
			int n2 = min(i + half, count);
			int mid = n2;
			int end = min(i + stride, count);

			int size = (i + stride > count) ? count - i : stride;
			for (int j = 0; j < size; ++j) {
				if ((a[n1] <= a[n2] || n2 >= end) && n1 < mid) {
					b[j + i] = a[n1++];
				}
				else {
					b[j + i] = a[n2++];
				}
			}
			memcpy(a + i, b + i, size * sizeof(int));
		}
		stride = stride << 1;
	}
}

void sort(int * a, int * b, int count) {
	int stride = 2;

	while ((stride >> 1) < count)
	{
		int half = stride >> 1;
		for (int i = 0; i < count; i += stride) {
			int n1 = i;
			int n2 = min(i + half, count);
			int mid = n2;
			int end = min(i + stride, count);

			int size = (i + stride > count) ? count - i : stride;
			for (int j = 0; j < size; ++j) {
				if ((a[n1] <= a[n2] || n2 >= end) && n1 < mid) {
					b[j + i] = a[n1++];
				}
				else {
					b[j + i] = a[n2++];
				}
			}
			memcpy(a + i, b + i, size * sizeof(int));
		}
		stride = stride << 1;
	}
}

int main()
{
	int countMax = 10241024;
	ofstream file;
	file.open("time_all.txt");

	for (int count = 1024; count <= countMax; count += 102400)
	{
		double start, end;
		int *a = new int[count];
		int *b = new int[count];
		int *c = new int[count];
		int *d = new int[count];
		int *e = new int[count];
		int *f = new int[count];
		int *w = new int[count]; //working array

		initArray(a, count);
		/*cout << "Init Array: " << endl;
		printArray(a, count);*/
		memcpy(b, a, count * sizeof(int));
		memcpy(c, a, count * sizeof(int));
		memcpy(d, a, count * sizeof(int));
		memcpy(e, a, count * sizeof(int));
		memcpy(f, a, count * sizeof(int));

		cout << "Count: " << count << endl;

		start = omp_get_wtime();
		sort(a, w, count);
		end = omp_get_wtime();
		/*cout << "Sorted Array: " << endl;
		printArray(a, count);*/
		cout << "Iterative serial time: " << end - start << endl;
		file << count << " " << "ist" << " " << end - start << endl;

		start = omp_get_wtime();
		sort_omp(b, w, count);
		end = omp_get_wtime();
		/*cout << "Sorted Array: " << endl;
		printArray(b, count);*/
		cout << "Iterative omp parallel time: " << end - start << endl;
		file << count << " " << "iomppt" << " " << end - start << endl;
	
		start = omp_get_wtime();
		sort_tbb(c, w, count);
		end = omp_get_wtime();
		/*cout << "Sorted Array: " << endl;
		printArray(b, count);*/
		cout << "Iterative tbb parallel time: " << end - start << endl;
		file << count << " " << "itbbpt" << " " << end - start << endl;

		start = omp_get_wtime();
		sort_rec(d, w, count);
		end = omp_get_wtime();
		/*cout << "Sorted Array: " << endl;
		printArray(c, count);*/
		cout << "Recursive serial time: " << end - start << endl;
		file << count << " " << "rst" << " " << end - start << endl;
	
		start = omp_get_wtime();
		sort_rec_omp(e, w, count, 1);
		end = omp_get_wtime();
		/*cout << "Sorted Array: " << endl;
		printArray(c, count);*/
		cout << "Recursive omp parallel time: " << end - start << endl;
		file << count << " " << "romppt" << " " << end - start << endl;

		start = omp_get_wtime();
		sort_rec_tbb(f, w, count);;
		end = omp_get_wtime();
		/*cout << "Sorted Array: " << endl;
		printArray(c, count);*/
		cout << "Recursive tbb parallel time: " << end - start << endl;
		file << count << " " << "rtbbpt" << " " << end - start << endl;

		if (!compareArrays(a, b, count))
			cout << "iError" << endl;
		else
			cout << "iPass" << endl;

		if (!compareArrays(c, d, count))
			cout << "rError" << endl;
		else
			cout << "rPass" << endl;

		delete[] w;
		delete[] f;
		delete[] e;
		delete[] d;
		delete[] c;
		delete[] b;
		delete[] a;
	}
}

