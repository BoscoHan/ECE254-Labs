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
	//printf("size of our struct is %d\n\n", sizeof(struct memory_list));

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
	struct memory_list *min_node = NULL; //= best_memory;

	//don't create new node if 0 requested
	if(size <= 0)
	{
		return NULL;
	}

	size_t adjusted_size = ((size + 4 - 1) / 4) * 4;

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

	if(min_node == NULL)
	{
		return NULL;
	}

	//if node size is exactly amount we need, just change status and return
	if(min_node->space == adjusted_size + sizeof(struct memory_list))
	{
		min_node->allocated = 1;
		min_node->space = adjusted_size;
		return min_node;
	}

	current = best_memory;
	//printf("\nMIN NODE SIZE %d %d\n", min_node->space, min_node->allocated);
	if(best_memory->next != NULL)
	{
	//reduce size of node
		while(current->next != NULL)
		{
			current = current->next; 
			//update min node to current if its unallocated, smaller than previous min and has enough space
			if(current->allocated == 0 && (current->space <= min_node->space) && (current->space >= (adjusted_size + sizeof(struct memory_list))))
			{
			min_node = current;
			}
		}
	}

	//printf("\nMIN NODE AFTER WHILE SIZE %d %d\n", min_node->space, min_node->allocated);
	//printf("\nSize + sizeof %d\n", size + sizeof(struct memory_list));

	// break if requested > size initialized
	if(min_node->allocated == 1 || min_node->space < adjusted_size)
	{
		return NULL;
	}

	//if size passed in is greater than left over space minus header
	if(adjusted_size > min_node->space - sizeof(struct memory_list))
	{
		min_node->allocated = 1;
		return min_node;
	}

	struct memory_list * new_node = (size_t)min_node +  sizeof(struct memory_list) + adjusted_size;
	//printf("\nnew node %lu\n", (unsigned long)new_node);

	if(min_node->next != NULL)
	{	
		struct memory_list * new_node = (size_t)min_node +  sizeof(struct memory_list) + adjusted_size;
		min_node->next->previous = new_node;
		new_node->next = min_node->next;
	}


	//add the new node in the list
	//update spaces
	 new_node->previous = min_node;
	 min_node->next = new_node;

	 new_node->allocated = 0;
	 new_node->space = min_node->space - adjusted_size - sizeof(struct memory_list);
	 
	 min_node->space = adjusted_size;
	 min_node->allocated = 1;

	// printf("MIN NODE END %d %d\n", min_node->space, min_node->allocated);
	 
	 //add struct size to return address
	 return (struct memory_list*)((size_t)min_node + sizeof(struct memory_list));
}

void *worst_fit_alloc(size_t size)
{	
	struct memory_list *current = worst_memory;
	struct memory_list *max_node = NULL; //= best_memory;

	//don't create new node if 0 requested
	if(size <= 0)
	{
		return NULL;
	}

	size_t adjusted_size = ((size + 4 - 1) / 4) * 4;
	

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

	if(max_node == NULL)
	{
		return NULL;
	}


	if(worst_memory->next != NULL)
	{
	//reduce size of node
		while(current->next != NULL)
		{
			current = current->next; 
			//update min node to current if its unallocated, smaller than previous min and has enough space
			if(current->allocated == 0 && current->space > max_node->space && current->space > adjusted_size + sizeof(struct memory_list))
			{
			max_node = current;
			}
		}
	}

	//if node size is exactly amount we need, just change status and return
	if(max_node->space == adjusted_size)
	{
		max_node->allocated = 1;
		max_node->space = adjusted_size;
		return max_node;
	}

	// break if requested > size initialized
	if(max_node->allocated == 1 || max_node->space < adjusted_size)
	{
		return NULL;
	}

	//if size passed in is greater than left over space minus header
	if(adjusted_size > max_node->space - sizeof(struct memory_list))
	{
		max_node->allocated = 1;
		return max_node;
	}

	struct memory_list * new_node = (size_t)max_node +  sizeof(struct memory_list) + adjusted_size;

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
	 new_node->space = max_node->space - adjusted_size - sizeof(struct memory_list);
	 
	 max_node->space = adjusted_size;
	 max_node->allocated = 1;
	
	 //add struct size to return address
	 return (struct memory_list*)((size_t)max_node + sizeof(struct memory_list));
}

/* memory de-allocator */
void coalesce (struct memory_list * node )
{	
	//next previous nodes
	struct memory_list * previous = node -> previous;
	struct memory_list * next = node -> next;	

	//5 cases

	//first and last
	if((previous == NULL && next->allocated == 1) || (next == NULL && previous->allocated == 1))
	{
		return;
	}
	//none free
	if ((previous == NULL && next == NULL) || (previous->allocated == 1 && next->allocated == 1))
	{
		//do nothing
		return;		
	}

	//previous free
	if ((previous != NULL && previous->allocated==0) && (next == NULL || next->allocated == 1 ))
	{
		//    0  ------ 0 ------- 1
		struct memory_list* temp = node;
		node = previous;
		if(previous != NULL)
		{
			node->previous = previous->previous;
		}
		if(previous->previous != NULL)
		{
			previous->previous->next = node;
		}
		
		node->next = temp->next;

		//update size and delete node
		node->space = temp->space + node->space + sizeof(struct memory_list);
	}

	//next free
	if ((next != NULL && next->allocated == 0) && (previous == NULL || previous->allocated == 1))
	{
		//   1  ------ 0 ------- 0
		node->next = next->next;
		if(next->next != NULL)
		{
			 next->next->previous= node;
		}
		//update size and delete node
		node->space = node->space + next->space + sizeof(struct memory_list);
	}

	//both free
	if((next != NULL && next->allocated == 0) && (previous != NULL && previous->allocated == 0))
	{
		node->next = next->next;
		if(next->next != NULL)
		{
			 next->next->previous= node;
		}
		//update size and delete node
		node->space = node->space + next->space + sizeof(struct memory_list);
		
		//call again to coalesce the previous
		coalesce(node);
	}
	
}

/* memory de-allocator */
void best_fit_dealloc(void *ptr) 
{
	struct memory_list * node;

	if((((struct memory_list *)ptr)->space) == 0)
	{
		node = (struct memory_list *)((size_t)ptr - sizeof(struct memory_list));
	}
	else
	{
		node = (struct memory_list *)((size_t)ptr);
	}

	node -> allocated = 0;
	
	// do coallasing here
	coalesce(node);			
	return;
}

void worst_fit_dealloc(void *ptr) 
{
	struct memory_list * node;
	if((((struct memory_list *)ptr)->space) == 0)
	{
		node = (struct memory_list *)((size_t)ptr - sizeof(struct memory_list));
	}
	else
	{
		node = (struct memory_list *)((size_t)ptr);
	}

	node -> allocated = 0;
	// do coallasing here
	coalesce(node);			
	return;
}

/* memory algorithm metric utility function(s) */

/* count how many free blocks are less than the input size */ 
int best_fit_count_extfrag(size_t size)
{
	int bf_count = 0;
	struct memory_list* current = best_memory;		
	while (current -> next != NULL) {
		if (current->allocated == 0 && current->space < size){
			bf_count++;
		}
		current = current->next;		
	}
	return bf_count;
}

int worst_fit_count_extfrag(size_t size)
{
	int wf_count = 0;
	struct memory_list * current = worst_memory; 
	while(current != NULL)
	{
		if(current->allocated == 0 && current->space < size )
		{
			wf_count++;
		}
		current = current->next;
	}
	return wf_count;
}

// test
// testing function to view memory of best fit (1) or worst fit (0)
void print_memory(int mem_type) {
	struct memory_list* current;
	
	if(mem_type == 0) 
	{
		current = (struct memory_list*)worst_memory;
	}
	
	else if(mem_type == 1) 
	{
		current = (struct memory_list*)best_memory;
	}

	while(current != NULL)
	{
		printf("Address: %lu\tSpace: %d\tState: %d\n",(size_t)current, current->space, current->allocated);
		current=current->next;
	}
}

