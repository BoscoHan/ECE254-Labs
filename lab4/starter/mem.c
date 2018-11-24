/**
 * @file memory.c
 * @brief: ECE254 Lab: memory allocation algorithm comparison template file
 * @author: 
 * @date: 2015-11-20
 */

/* includes */
#include <stdio.h> 
#include <stdlib.h> 
#include "mem.h"

/* defines */

struct memory_list
{
	size_t * address;
	size_t space;
	int allocated; //0 = unallocated, 1 = allocated

	struct list * previous;
	struct list * next;
};

/* global variables */
struct memory_list best_memory;
struct memory_list worst_memory;


/* Functions */

/* memory initializer */
int best_fit_memory_init(size_t size)
{
	// To be completed by students
	if(size < sizeof(struct memory_list))
	{
		return -1;
	}

	best_memory.address = malloc(size);
	best_memory.space = size;
	best_memory.allocated = 0;
	best_memory.previous = NULL;
	best_memory.next = NULL;

	if(best_memory.address == NULL)
	{
		return -1;
	}

	return 0;
}

int worst_fit_memory_init(size_t size)
{

	// To be completed by students
	if(size < sizeof(struct memory_list))
	{
		return -1;
	}

	worst_memory.address = malloc(size);
	worst_memory.space = size;
	worst_memory.allocated = 0;
	worst_memory.previous = NULL;
	worst_memory.next = NULL;

	if(worst_memory.address == NULL)
	{
		return -1;
	}

	return 0;
}

/* memory allocators */
void *best_fit_alloc(size_t size)
{
	//reduce size of node

	//create new next node
	
	// To be completed by students
	return NULL;
}


void *worst_fit_alloc(size_t size)
{
	// To be completed by students
	return NULL;
}

/* memory de-allocator */
void best_fit_dealloc(void *ptr) 
{

	// To be completed by students
	return;
}

void worst_fit_dealloc(void *ptr) 
{

	// To be completed by students
	return;
}

/* memory algorithm metric utility function(s) */

/* count how many free blocks are less than the input size */ 
int best_fit_count_extfrag(size_t size)
{
	// To be completed by students
	return 0;
}

int worst_fit_count_extfrag(size_t size)
{
	// To be completed by students
	return 0;
}
