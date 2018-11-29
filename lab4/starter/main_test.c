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
	printf("\nTest 1 Worst Fit - expected states: 1 1 0\n");
	worst_fit_memory_init(1000);
	worst_fit_alloc(499);
	worst_fit_alloc(159);
	print_mem_info(0);
	return;
}

void test2_worst_fit() {
	//alloc full test
	printf("\nTest 2 Worst Fit - expected states: 1 1 1 1\n");
	worst_fit_memory_init(1000);
	worst_fit_alloc(299);
	worst_fit_alloc(199);
	worst_fit_alloc(428);
	// ---- full--------
	worst_fit_alloc(100);
	worst_fit_alloc(100);
	print_mem_info(0);
	return;
}

void test3_worst_fit() {
	//simple alloc and dealloc - no coalescing required
	printf("\nTest 3 Worst Fit - expected states 1 1 1 1\n");
	worst_fit_memory_init(1000);
	void * top = worst_fit_alloc(299);
	worst_fit_alloc(199);
	worst_fit_alloc(428);
	// ---- full--------
	//deallocate the top node
	worst_fit_dealloc(top);
	// -- alloc again --
	worst_fit_alloc(100);
	worst_fit_alloc(174);
	print_mem_info(0);
	return;
}

void test4_worst_fit()
{
	//alloc and dealloc -- coalesce top
	printf("\nTest 4 Worst Fit - expected states: 1 1 1\n");
	worst_fit_memory_init(1000);
	void * top = worst_fit_alloc(299);
	void * middle = worst_fit_alloc(199);
	worst_fit_alloc(428);
	// ---- full--------
	//deallocate top node then middle node
	worst_fit_dealloc(top);
	worst_fit_dealloc(middle);
	//allocate again
	worst_fit_alloc(280);
	worst_fit_alloc(220);
	//----- full -------
	worst_fit_alloc(200);

	print_mem_info(0);
	return;
}

void test5_worst_fit()
{
	//alloc and dealloc -- coalesce top
	printf("\nTest 5 Worst Fit - expected states: 1 1 1 1 0\n");
	worst_fit_memory_init(1000);
	worst_fit_alloc(299);
	worst_fit_alloc(299);
	void * middle = worst_fit_alloc(199);
	void * bottom = worst_fit_alloc(24);
	worst_fit_alloc(24);
	// ---- full--------
	//deallocate bottom node then middle node
	 worst_fit_dealloc(bottom);
	 worst_fit_dealloc(middle);
	// //allocate again
	 worst_fit_alloc(245);
	// //----- full -------
	 worst_fit_alloc(200);

	print_mem_info(0);
	return;
}

//( ͡ಠ ʖ̯ ͡ಠ)╭∩╮
void test6_worst_fit()
{
	//alloc and dealloc -- coalesce top and bottom
	printf("\nTest 6 Worst Fit - expected states: 0\n");
	worst_fit_memory_init(1000);
	void * top = worst_fit_alloc(299);
	void * middle = worst_fit_alloc(199);
	void * bottom = worst_fit_alloc(428);
	// ---- full--------
	//deallocate top node then middle node
	worst_fit_dealloc(top);
	worst_fit_dealloc(middle);
	//allocate again
	void * a = worst_fit_alloc(280);
	void * b = worst_fit_alloc(220);
	//----- full -------
	worst_fit_alloc(200);

	//dealloc top, bottom, then middle
	 worst_fit_dealloc(a);
	 worst_fit_dealloc(bottom);
	 worst_fit_dealloc(b);

	print_mem_info(0);
	return;
}

/////////////////////////////////
void test1_best_fit() {
	//simple alloc only test
	printf("\nTest 1 best Fit - expected states: 1 1 0\n");
	best_fit_memory_init(1000);
	best_fit_alloc(499);
	best_fit_alloc(159);
	print_mem_info(1);
	return;
}

void test2_best_fit() {
	//alloc full test
	printf("\nTest 2 best Fit - expected states: 1 1 1 1\n");
	best_fit_memory_init(1000);
	best_fit_alloc(299);
	best_fit_alloc(199);
	best_fit_alloc(428);
	// ---- full--------
	best_fit_alloc(100);
	best_fit_alloc(100);
	print_mem_info(1);
	return;
}

void test3_best_fit() {
	//simple alloc and dealloc - no coalescing required
	printf("\nTest 3 best Fit - expected states 1 1 1 1\n");
	best_fit_memory_init(1000);
	void * top = best_fit_alloc(299);
	best_fit_alloc(199);
	best_fit_alloc(428);
	// ---- full--------
	//deallocate the top node
	best_fit_dealloc(top);
	// -- alloc again --
	best_fit_alloc(100);
	best_fit_alloc(174);
	print_mem_info(1);
	return;
}

void test4_best_fit()
{
	//alloc and dealloc -- coalesce top
	printf("\nTest 4 best Fit - expected states: 1 1 1\n");
	best_fit_memory_init(1000);
	void * top = best_fit_alloc(299);
	void * middle = best_fit_alloc(199);
	best_fit_alloc(428);
	// ---- full--------
	//deallocate top node then middle node
	best_fit_dealloc(top);
	best_fit_dealloc(middle);
	//allocate again
	best_fit_alloc(280);
	best_fit_alloc(220);
	//----- full -------
	best_fit_alloc(200);

	print_mem_info(1);
	return;
}

void test5_best_fit()
{
	//alloc and dealloc -- coalesce top
	printf("\nTest 5 best Fit - expected states: 1 1 1 1 0\n");
	best_fit_memory_init(1000);
	best_fit_alloc(299);
	best_fit_alloc(299);
	void * middle = best_fit_alloc(199);
	void * bottom = best_fit_alloc(24);
	best_fit_alloc(24);
	// ---- full--------
	//deallocate bottom node then middle node
	 best_fit_dealloc(bottom);
	 best_fit_dealloc(middle);
	// //allocate again
	 best_fit_alloc(245);
	// //----- full -------
	 best_fit_alloc(200);

	print_mem_info(1);
	return;
}

//( ͡ಠ ʖ̯ ͡ಠ)╭∩╮
void test6_best_fit()
{
	//alloc and dealloc -- coalesce top and bottom
	printf("\nTest 6 best Fit - expected states: 0\n");
	best_fit_memory_init(1000);
	void * top = best_fit_alloc(299);
	void * middle = best_fit_alloc(199);
	void * bottom = best_fit_alloc(428);
	// ---- full--------
	//deallocate top node then middle node
	best_fit_dealloc(top);
	best_fit_dealloc(middle);
	//allocate again
	void * a = best_fit_alloc(280);
	void * b = best_fit_alloc(220);
	//----- full -------
	best_fit_alloc(200);

	//dealloc top, bottom, then middle
	 best_fit_dealloc(a);
	 best_fit_dealloc(bottom);
	 best_fit_dealloc(b);

	print_mem_info(1);
	return;
}

//̿̿ ̿̿ ̿̿ ̿'̿'\̵͇̿̿\з= ( ▀ ͜͞ʖ▀) =ε/̵͇̿̿/’̿’̿ ̿ ̿̿ ̿̿ ̿̿
void test4_large_allocation(){
	best_fit_memory_init(9000000);
	print_mem_info(1);
	return;
}

//¯\_(⊙_ʖ⊙)_/¯
int main(int argc, char *argv[]) {
	// worst fit tests
	printf("\n---BEST FIT TESTS---\n");
	test1_worst_fit();
	test2_worst_fit();
	test3_worst_fit();
	test4_worst_fit();
	test5_worst_fit();
	test6_worst_fit();

	//best fit tests
	printf("\n---WORST FIT TESTS---\n");
	test1_best_fit();
	test2_best_fit();
	test3_best_fit();
	test4_best_fit();
	test5_best_fit();
	test6_best_fit();

	// test4_large_allocation();
	return 0;
}