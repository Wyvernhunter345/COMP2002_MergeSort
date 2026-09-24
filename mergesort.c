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
}

/* this function will be called by parallel_mergesort() as its base case. */
void my_mergesort(int left, int right){
	printf("Reached Base Case\n");
	fflush(stdout);

}

/* this function will be called by the testing program. */
void * parallel_mergesort(void *arg){
	struct argument *variables = (struct argument *) arg;
	printf("We at level %u\n", variables->level);
	fflush(stdout);

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
	struct argument
	{
		int left;
		int right;
		int level;
	};
	
	struct argument *arg = malloc(sizeof(struct argument));
	arg->left = left;
	arg->right = right;
	arg->level = level;
	
	// all params will be included in this one struct - this goes to parallel_mergesort
	return arg;
}

