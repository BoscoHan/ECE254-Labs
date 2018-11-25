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

	if(size < sizeof(struct memory_list) + 4)
	{
		return -1;
	}

	best_memory = malloc(size);

	if(best_memory == NULL)
	{
		return -1;
	}

	//initialize memory
	best_memory = (struct memory_list*)((size_t)best_memory +  sizeof(struct memory_list));
	best_memory->space = size - sizeof(struct memory_list);
	best_memory->allocated = 0;
	best_memory->previous = NULL;
	best_memory->next = NULL;

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

	//initiliaze the memory
	worst_memory = (struct memory_list*)((size_t)worst_memory +  sizeof(struct memory_list));
	worst_memory->space = size - sizeof(struct memory_list);
	worst_memory->allocated = 0;
	worst_memory->previous = NULL;
	worst_memory->next = NULL;

	return 0;
}

/* memory allocators */
void *best_fit_alloc(size_t size)
{

	struct memory_list *current = best_memory;
	struct memory_list *min_node; //= best_memory;

	//don't create new node if 0 requested
	if(size == 0)
	{
		return NULL;
	}

	//initialize starting position of min_node to first allocated node
	while(current != NULL)
	{
		if(current->allocated == 0)
		{
			min_node = current;
			break;
		}
		current = current->next;
	}
	
	if(best_memory->next != NULL)
	{
	//reduce size of node
		while(current->next != NULL)
		{
			current = current->next; 
			//update min node to current if its unallocated, smaller than previous min and has enough space
			if(current->allocated == 0 && current->space < min_node->space && current->space > size + sizeof(struct memory_list))
			{
			min_node = current;
			}
		}
	}
	
	// break if requested > size initialized
	if(min_node->allocated == 1 || min_node->space < size + sizeof(struct memory_list))
	{
		printf("\nThere is no min node\n");
		return NULL;
	}

	//if node size is exactly amount we need, just change status and return
	if(min_node->space == size)
	{
		printf("\nexact fit\n");
		min_node->allocated = 1;
		return min_node;
	}

	struct memory_list * new_node = (size_t)min_node +  sizeof(struct memory_list) + size;
	//printf("\nnew node %lu\n", (unsigned long)new_node);

	if(min_node->next != NULL)
	{
		min_node->next->previous = new_node;
		new_node->next = min_node->next;
	}

	//add the new node in the list
	//update spaces
	 new_node->previous = min_node;
	 min_node->next = new_node;

	 new_node->allocated = 0;
	 new_node->space = min_node->space - size - sizeof(struct memory_list);
	 
	 min_node->space = size;
	 min_node->allocated = 1;

	 //add struct size to return address
	 return (struct memory_list*)((size_t)min_node + sizeof(struct memory_list));
}


void *worst_fit_alloc(size_t size)
{	
	struct memory_list *current = worst_memory;
	struct memory_list *max_node; //= best_memory;

	//don't create new node if 0 requested
	if(size == 0)
	{
		return NULL;
	}

	//initialize starting position of min_node to first allocated node
	while(current != NULL)
	{
		if(current->allocated == 0)
		{
			max_node = current;
			break;
		}
		current = current->next;
	}

	if(worst_memory->next != NULL)
	{
	//reduce size of node
		while(current->next != NULL)
		{
			current = current->next; 
			//update min node to current if its unallocated, smaller than previous min and has enough space
			if(current->allocated == 0 && current->space > max_node->space && current->space > size + sizeof(struct memory_list))
			{
			max_node = current;
			}
		}
	}

	// break if requested > size initialized
	if(max_node->allocated == 1 || max_node->space < size + sizeof(struct memory_list))
	{
		printf("\nThere is no max node\n");
		return NULL;
	}

	//if node size is exactly amount we need, just change status and return
	if(max_node->space == size)
	{
		printf("\nexact fit\n");
		max_node->allocated = 1;
		return max_node;
	}

	struct memory_list * new_node = (size_t)max_node +  sizeof(struct memory_list) + size;

	//add the new node in the list
	//update spaces
	if(max_node->next != NULL)
	{
		max_node->next->previous = new_node;
		new_node->next = max_node->next;
	}

	 new_node->previous = max_node;
	 max_node->next = new_node;

	 new_node->allocated = 0;
	 new_node->space = max_node->space - size - sizeof(struct memory_list);
	 
	 max_node->space = size;
	 max_node->allocated = 1;
	
	 //add struct size to return address
	 return (struct memory_list*)((size_t)max_node + sizeof(struct memory_list));
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
