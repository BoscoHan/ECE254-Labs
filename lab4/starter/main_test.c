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



int main(int argc, char *argv[]) {
	printf("\nstart test\n");
	test1_best_fit();
	return 0;
}

void test1_best_fit() {
	// best_fit_memory_init(500);
	// best_fit_alloc(100);
	printf("\nTest 1 Best Fit \n");
	best_fit_memory_init(1000);

	// best_fit_alloc(200);
	// best_fit_alloc(200);
	best_fit_alloc(1);
	best_fit_alloc(200);
	best_fit_alloc(100);
	best_fit_alloc(0);
	best_fit_alloc(200);
	best_fit_alloc(200);
	best_fit_alloc(500);

	print_mem_info(1);

	//best_fit_alloc

	// void* a = best_fit_alloc(200);
	// //best_fit_alloc(220);
	// void* c = best_fit_alloc(220);
	// best_fit_alloc(200);

	// printf("Full\n");
	// print_mem_info(1);
	// printf("---\n");

	// best_fit_alloc(100);
	// printf("Allocated 100, should go into block 1\n");
	// print_mem_info(1);
	// printf("---\n");

	return;
}

