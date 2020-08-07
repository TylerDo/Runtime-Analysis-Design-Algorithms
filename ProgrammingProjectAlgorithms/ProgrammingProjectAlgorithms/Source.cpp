#include <iostream>
using namespace std;
/*
The Selection Problem
The selection problem seeks to find the ith order statistic in a set A of
n distinct numbers, where 1 <= i <= n.

Given an array A[1...n] of n elements, find the ith order statistic
*/

//Global Variables
int size = 200;
int *ptr;
int A[];
int i;
int n;
int N[];

//Prototypes
void setN();//Set the n values 10000,20000,30000,40000,....2000000. iterates 200 times



int main() {
	setN();
	for (int i = 0; i <= 200; i++)
	{
		cout << N[i] << endl;
	}

	return 0;
}

void setN() {
	for (int i = 0; i <= 200; i++)
	{
		N[i] += 10000;
	}
}

int getn(int N[]) {

}
/*
First Algorithm ALG1: RT = O(n^2)
Strategy: sort the array A using Insertion sort and return A[i]
pseudocode using A[1...n]: INSERTION-SORT(A,n) Return A[i]
*/

/*
Second Algorithm ALG2: RT = O(nlgn)
Strategy: sort the array A using Heapsort and return A[i]
Pseudocode using A[1...n]: HEAPSORT(A,n) Return A[i]
*/

/*
Third Algorithm ALG3: Expected RT O(n)
Strategy: use the RANDOMIZED-SELECT algorithm from textbook/notes 
Pseudocode using A[1...n]: Return RANDOMIZED-SELECT(A, 1, n, i)
*/