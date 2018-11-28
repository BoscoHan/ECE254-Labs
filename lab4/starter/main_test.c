/**
  * ECE254 Linux Dynamic Memory Management Lab
  * @file: main_test.c
  * @brief: The main file to write tests of memory allocation algorithms
  */ 

/* includes */
/* system provided header files. You may add more */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* non-system provided header files. 
   Do not include more user-defined header files here
 */
#include "mem.h"
// TODO: void print_mem_info(){}

// tests completely filling the mem space and deallocates two blocks and then allocates one into the larger free block
void test1_worst_fit() {
	//simple alloc only test
	printf("Test 1 Worst Fit \n");
	worst_fit_memory_init(1000);
	void* a = worst_fit_alloc(499);
	worst_fit_alloc(159);
	//worst_fit_alloc(400);
	// //worst_fit_dealloc(a);
	print_mem_info(0);
	return;
}

int main(int argc, char *argv[]) {
	test1_worst_fit();
	return 0;
}

