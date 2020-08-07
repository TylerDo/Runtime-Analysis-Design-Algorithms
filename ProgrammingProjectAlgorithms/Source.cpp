/*
Programming Project Tyler Do

Selection Problem: given an array A[i...n] of n elements, find the ith order statistic where 1 <= i <= n. 
min = i, max = n
Input: A set A of n(distinct) numbers and an integer i
Output: The ith order statistic element of A
*/
#include <iostream>
#include <ctime>
#include <time.h>
#include <chrono>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
using namespace std;

void ALG1(vector<int> v, int n, int i);//Vector, size, ith statistic
void InsertionSort(vector<int>& v, int n);//Insertion sort vector A
void ALG2(vector<int> v, int n, int i);//Vector, size, ith statistic
void HeapSort(vector<int> v, int n);//HeapSort vector A
void buildMaxHeap(vector<int>& v, int n);//Build Max Heap for vector A
void maxHeapify(vector<int> v,int i, int n);//Max heapify index of vector 
void ALG3(vector<int> v, int n, int i);//Vector, size, ith statistc
int randomizedSelect(vector<int>& v,int p,int r,int i);//Vector, start, end, pivot
int randomizedPartition(vector<int>& v,int p,int r);//Vector, start, end
int partition(vector<int>& v, int p, int r);//Vector, start, end
int parent(int i);//Parent node
int left(int i);//Left child node
int right(int i);//Right child node


int n = 20001;//Size
int i;//ith Statistic. ie i = 3 ith statistic is 3rd smallest element
int m = 5;//Iterations
double count;
vector<vector<int>> C (m, vector<int>(n));//Vector C with m rows and n columns
vector<int> A;//Vector to copy
double avgRt = 0;

int main() {

	//Generate numbers for vector A[1...m, 1...n]
	//Initialize random seed
	srand(time(NULL));
	for (int j = 0; j <= m - 1; j++)//Iterations
	{
		for (int k = 0; k < n; k++)//Input sizes
		{
			C[j][k] = rand();//Row j by column k
		}
	}
	/*	Display the 2d Vector C
	for (int i = 0; i < C.size(); i++) {
		for (int j = 0; j < C[i].size(); j++)
			cout << C[i][j] << " ";
		cout << endl << "Original vectors above!" << endl;
	}
	*/

	//Measurements for ALG1
	for (int ns = 1000; ns <= 20000; ns += 1000)
	{
		double count = 0;
		double accumulator;
		i = (2 * ns) / 3;
		for (int j = 0; j < m; j++)
		{
			for (int k = 0; k < n; k++)
			{
				A.push_back(C[j][k]);//Copy the values into A
			}
			auto start = chrono::steady_clock::now();//Start clock
			ALG1(A, ns, i);
			auto end = chrono::steady_clock::now();//Stop clock
			double rt = double(std::chrono::duration_cast <chrono::nanoseconds> (end - start).count());
			count += rt;
			A.clear();
		}
		accumulator = count / 5;
		avgRt = accumulator;
		cout << endl << " Using insertion sort: " << " average runtime " << accumulator << " miliseconds!" << endl;
		cout << "Runtime above for " << ns << " Inputs!" << endl;
		avgRt = 0;
	}
	//Measurements for ALG2
	for (int ns = 1000; ns <= 20000; ns += 1000)
	{
		double count = 0;
		double accumulator;
		i = (2 * ns) / 3;
		for (int j = 0; j < m; j++)
		{
			for (int k = 0; k < n; k++)
			{
				A.push_back(C[j][k]);//Copy values into A
			}
			auto start = chrono::steady_clock::now();//Start clock
			ALG2(A, ns, i);
			auto end = chrono::steady_clock::now();//End clock
			double rt = double(std::chrono::duration_cast <chrono::milliseconds> (end - start).count());
			count += rt;
			A.clear();
		}
		accumulator = count / 5;
		avgRt = accumulator;
		cout << " Using Heap sort: " << " average runtime " << accumulator << " miliseconds!" << endl;
		cout << " Runtime above for " << ns << " Inputs!" << endl;
		avgRt = 0;
	}
	//Measurements for ALG3
	for (int ns = 1000; ns <= 20000; ns += 1000)
	{
		double count = 0;
		double accumulator;
		i = (2 * ns) / 3;
		for (int j = 0; j < m; j++)
		{
			for (int k = 0; k < n; k++)
			{
				A.push_back(C[j][k]);//Copy values into A
			}
			auto start = chrono::steady_clock::now();//Start clock
			ALG3(A, ns, i);
			auto end = chrono::steady_clock::now();//End clock
			double rt = double(std::chrono::duration_cast <chrono::milliseconds> (end - start).count());
			count += rt;
			A.clear();
		}
		accumulator = count / 5;
		avgRt = accumulator;
		cout << " Using Randomized select: " << " average runtime " << accumulator << " miliseconds!" << endl;
		cout << " Runtime above for " << ns << " Inputs!" << endl;
		avgRt = 0;
	}
	cout << "Runtime Complete!" << endl;
	return 0;
}
/*
ALG1
strategy:sort the vector v using Insertion sort and return v[i]
*/
void ALG1(vector<int> v, int n, int i) {
	InsertionSort(v, n);
	cout << endl << "Insertion Sort ith iteration: " << v[i];//Smallest ith iteration
}
/*
Insertion Sort
*/
void InsertionSort(vector<int>& v, int n) {
	int i = 0;
	int key = 0;
	for (int j = 1; j < n; j++)
	{
		key = v[j];
		i = j - 1;
		while (i >= 0 && v[i] >= key)
		{
			v[i + 1] = v[i];
			i = i - 1;
		}
		v[i + 1] = key;
	}
}
/*
ALG2
strategy: sort the vector v using Heapsort and return v[i]
*/
void ALG2(vector<int> v, int n, int i) {
	HeapSort(v, n);
	cout << endl << "HeapSort ith itertation: " << v[i];//Smallest ith iteration
}
/*
HeapSort
*/
void HeapSort(vector<int> v, int n) {
	buildMaxHeap(v, n);
	for (int i = n - 1; i >= 1; i--)//Remove last element from heap
	{
		int temp = v[1];//swap
		v[1] = v[i];
		v[i] = temp;
		v.erase(v.begin() + v.size() - 1);//Delete node
		maxHeapify(v, 1, i);//Heapify reduced heap
	}
}
/*
buildMaxheap
*/
void buildMaxHeap(vector<int>& v, int n){
	for (int i = (int)floor(n / 2); i >= 1; i--)
	{
		maxHeapify(v, i, n);
	}
}
/*
Max Heapifty
Parent(i) = i/2
Left Child(i) = 2*i
Right Child(i) = 2*i + 1
*/
void maxHeapify(vector<int> v, int i, int n){
	int largest = 0;
	int l = left(i);
	int r = right(i);
	if ((l <= n - 1) && (v[l] > v[i]))
	{
		largest = l;
	}
	else
	{
		largest = i;
	}
	if ((r <= n - 1) && (v[r] > v[largest]))
	{
		largest = r;
	}
	if (largest != i)
	{
		int temp = v[i];
		v[i] = v[largest];
		v[largest] = temp;
		maxHeapify(v, largest, n);
	}
}
/*
Parent
*/
int parent(int i) {
	return (i / 2);
}
/*
left
*/
int left(int i) {
	return (2 * i);
}
/*
right
*/
int right(int i) {
	return ((2 * i) + 1);
}
/*
ALG3
strategy: use the Randomized-Select algorithm
*/
void ALG3(vector<int> v, int n, int i) {
	int x = randomizedSelect(v, 1, n, i);
	cout << "Randomized Select iteration: " << x << endl;
}
/*
RandomizedSelect
*/
int randomizedSelect(vector<int>& v,int p,int r,int i) {
	int q;
	int k;
	if (p == r)
	{
		return v[p];
	} 
	q = randomizedPartition(v, p, r);
	k = q - p + 1;
	if (i == k)
	{
		return v[q];
	}
	else if (i < k)
	{
		return randomizedSelect(v, p, q - 1, i);
	}
	else// i > k
	{
		return randomizedSelect(v, q + 1, r, i - k);
	}
}
/*
Randomized Partition
*/
int randomizedPartition(vector<int>& v, int p, int r) {
	int i;
	i = rand() % r + 1;
	int temp = v[r];//swap
	v[r] = v[i];
	v[i] = temp;
	return partition(v, p, r);
}
/*
Partition
*/
int partition(vector<int>& v, int p, int r) {
	int x;
	int i;
	x = v[r];
	i = p - 1;
	for (int j = p; j < r - 1; j++)
	{
		if (v[j] <= x)
		{
			i = i + 1;
			int temp = v[i];//swap
			v[i] = v[j];
			v[j] = temp;
		}
	}
	int temp2 = v[i + 1];//swap
	v[i + 1] = v[r];
	v[r] = temp2;
	return i + 1;
}