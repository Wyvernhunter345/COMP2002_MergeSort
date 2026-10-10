/**
 * This file implements parallel mergesort.
 */

#include <stdio.h>
#include <string.h> /* for memcpy */
#include <stdlib.h> /* for malloc */
#include <pthread.h>
#include "mergesort.h"

/* this function will be called by mergesort() and also by parallel_mergesort(). */
void merge(int leftstart, int leftend, int rightstart, int rightend){
	
	// initialise index variables for the left and right subarrays (i and j), and variable for the merged/temporary array (k)
	int i, j, k;
	i = leftstart;
	j = rightstart;
	k = leftstart;

	// merge the two subarrays (A) into the temporary array (B)
	while (i <= leftend && j <= rightend)
	{
		// compare the elements of the left and right subarrays and copy the smaller element into the temporary array
		// if the left subarray element is smaller or equal, copy it into the temporary array
		if (A[i] <= A[j])
		{
			B[k] = A[i];
			i++; // iterate to the next element in the left subarray for comparison
		}
		// if the right subarray element is smaller, copy it into the temporary array
		else
		{
			B[k] = A[j];
			j++; // iterate to the next element in the right subarray for comparison
		}
		k++; // iterate to the next element in the temporary array for copying
	}


	// copy any leftover/remaining elements of the left subarray into the temporary array
	while (i <= leftend)
	{
		B[k] = A[i];
		i++;
		k++;
	}

	// copy any leftover/remaining elements of the right subarray into the temporary array
	while (j <= rightend)
	{
		B[k] = A[j];
		j++;
		k++;
	}

	// copy the merged elements back into the original array
	memcpy(A + leftstart, B + leftstart, (rightend - leftstart + 1) * sizeof(int));
}

/* this function will be called by parallel_mergesort() as its base case. */
void my_mergesort(int left, int right){

	// base case: if the left index is greater than or equal to the right index, return (the array is already sorted)
	// e.g. if the array has only one element (sorted), or if the left index is greater than the right index (invalid)
	if (left >= right)
	{
		return;
	}

	// find the middle index of the array
	int mid = left + (right - left) / 2;

	// recursively sort the left half of the array using left and mid as the new left and right indices
	// calls my_mergesort() on the left half of the array (from left to mid) until the base case is reached
	my_mergesort(left, mid);

	// recursively sort the right half of the array using mid + 1 and right as the new left and right indices
	// calls my_mergesort() on the right half of the array (from mid + 1 to right) until the base case is reached
	my_mergesort(mid + 1, right);

	// merge the two sorted halves of the array
	merge(left, mid, mid + 1, right);

}

/* this function will be called by the testing program. */
void * parallel_mergesort(void *arg){
	struct argument *variables = (struct argument *) arg;

	// Base case
	if (variables->level == 0)
	{
		my_mergesort(variables->left, variables->right);
		return NULL;
	}

	// Recursive case
	pthread_t p1, p2;
	
	variables->level = variables->level - 1;
	struct argument *var1 = variables;
	struct argument *var2 = variables;
	
	pthread_create(&p1, NULL, parallel_mergesort, var1);
	pthread_create(&p2, NULL, parallel_mergesort, var2);
	pthread_join(p1, NULL);
	pthread_join(p2, NULL);
	return NULL;
}

/* we build the argument for the parallel_mergesort function. */
struct argument * buildArgs(int left, int right, int level){
	typedef struct argument
	{
		int left;
		int right;
		int level;
	} argument;
	
	argument *arg = malloc(sizeof(argument));
	arg->left = left;
	arg->right = right;
	arg->level = level;
	
	// all params will be included in this one struct - this goes to parallel_mergesort
	return arg;
}

