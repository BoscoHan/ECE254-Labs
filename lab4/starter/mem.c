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

/* global variables */
struct memory_list *best_memory;
struct memory_list *worst_memory;


/* Functions */

/* memory initializer */
int best_fit_memory_init(size_t size)
{
	printf("size of our struct is %d\n\n", sizeof(struct memory_list));
	// To be completed by students
	if(size < sizeof(struct memory_list) + 4)
	{
		return -1;
	}

	best_memory = malloc(size);

	if(best_memory == NULL)
	{
		return -1;
	}

	best_memory->address = best_memory +  sizeof(struct memory_list);
	best_memory->space = size - sizeof(struct memory_list);
	best_memory->allocated = 0;
	best_memory->previous = NULL;
	best_memory->next = NULL;

	//printf("\nbest init %lu\n", best_memory->address);

	return 0;
}

int worst_fit_memory_init(size_t size)
{
	// To be completed by students
	if(size < sizeof(struct memory_list) + 4)
	{
		return -1;
	}

	worst_memory = malloc(size);

	if(worst_memory == NULL)
	{
		return -1;
	}

	worst_memory->address = worst_memory +  sizeof(struct memory_list);
	worst_memory->space = size - sizeof(struct memory_list);
	worst_memory->allocated = 0;
	worst_memory->previous = NULL;
	worst_memory->next = NULL;

	printf("\nworst init %lu\n", worst_memory->address);

	return 0;
}

/* memory allocators */
void *best_fit_alloc(size_t size)
{

	//can't be less than struct size
	if (size < sizeof(struct memory_list)){
		//return -1;
	}

	struct memory_list *current = best_memory;
	struct memory_list *min_node = 0;
	
	//reduce size of node
	while(current->next != NULL)
	{
		//update min node to current if its unallocated, smaller than previous min and has enough space
		if(current->allocated == 0 && current->space < min_node->space && current->space > size)
		{
		  min_node = current;
		}
		current = current->next; 
	}

	if(!min_node)
	{
		return 0;
	}

	//if node size is exactly amount we need, just change status and return
	if(min_node->space == size + sizeof(struct memory_list))
	{
		min_node->allocated = 1;
		return min_node->address;
	}

	//create new next node
	struct memory_list * new_node;
	new_node->address = min_node->address + size;// + sizeof(struct memory_list);
	new_node->space = min_node->space;// - sizeof(struct memory_list);
	
	//allocate node
	min_node->allocated = 1;
	min_node->space = size;

	//link nodes
	new_node->next = min_node->next;
	new_node->previous = min_node;
	min_node->next = new_node;
	struct memory_list * temp = new_node->next;
	temp->previous = new_node;

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

void test()
{
	printf("\ntest function called");
}

// test
// testing function to view memory of best fit (1) or worst fit (0)
void print_mem_info(int type) {
	struct memory_list* traverse;
	if(type == 0) {
		traverse = (struct memory_list*)worst_memory;
	}
	else if(type == 1) {
		traverse = (struct memory_list*)best_memory;
	}
	
	while(traverse != NULL){
		printf("Control Address: %lu\tSize: %d\tState: %d\n",
			(long unsigned int)traverse, traverse->space, traverse->allocated);
		traverse=traverse->next;
	}
}
