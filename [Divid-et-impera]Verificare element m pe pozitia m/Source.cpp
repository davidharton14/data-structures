#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
void swap(int* xp, int* yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

// Function to perform Selection Sort
void selectionSort(int* arr, int n)
{
	int i, j, min_idx;

	// One by one move boundary of unsorted subarray
	for (i = 0; i < n - 1; i++) {

		// Find the minimum element in unsorted array
		min_idx = i;
		for (j = i + 1; j < n; j++)
			if (arr[j] < arr[min_idx])
				min_idx = j;

		// Swap the found minimum element
		// with the first element
		swap(&arr[min_idx], &arr[i]);
	}
}

// Function to print an array
void printArray(int* arr, int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

int cautare(int*v,int n) {
	int nr=0,sw=0;
	for(int i=0;i<n;i++){
		if (i == v[i]) {
			nr = i;
			sw = 1;
			i = n;
		}
	}
	
	return nr;
	
}
int BinarySearch(int*v, int left, int right,int x) {            
	   
	while (left <= right) {
		int mid = (left + right) / 2;       

		if (x == v[mid]) 
			return mid;
		if (x < v[mid])  right = mid - 1;
		if (x > v[mid])  left = mid + 1;
		
	} 
	return -1;
}

int main()
{
	int n,numar,k=0;
	printf("n=");
	scanf("%d", &n);
	int* arr = (int*)malloc(sizeof(int)*n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &numar);
		arr[i] = numar;
	}
	printf("Original array: \n");
	printArray(arr, n);

	selectionSort(arr, n);
	printf("\nSorted array in Ascending order: \n");
	printArray(arr, n);
	int x;
	x = cautare(arr, n);
	int pos;
	pos=BinarySearch(arr, 0, n - 1,x);
	if (pos != -1)
		printf("Pozitia care corespunde cu elementul este:%d", pos);
	else
		printf("Elementul nu a fost gasit");
	return 0;
}