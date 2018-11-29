/*
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

/* TEST 1: allocates two blocks, leaving one empty with remaining space
*/
void test1_worst_fit() {
	//simple alloc only test
	printf("\nTest 1 Worst Fit - expected states: 1 1 0\n");
	worst_fit_memory_init(1000);
	worst_fit_alloc(499);
	worst_fit_alloc(159);
	print_memory(0);
	return;
}

/* TEST 2: allocates 4 blocks which completely fill the memory,
	tries to allocate a fifth but is unsuccesful because there is no space
*/
void test2_worst_fit() {
	//alloc full test
	printf("\nTest 2 Worst Fit - expected states: 1 1 1 1\n");
	worst_fit_memory_init(1000);
	worst_fit_alloc(299);
	worst_fit_alloc(199);
	worst_fit_alloc(428);
	worst_fit_alloc(100);
	// ---- full--------
	worst_fit_alloc(100);
	print_memory(0);
	return;
}

/* TEST 3: allocates 3 blocks then deallocates the top block,
	then allocates two more blocks tomake sure allcoation works after deallocation
*/
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
	print_memory(0);
	return;
}

/* TEST 4: COALESCE TOP - allocates 3 blocks, then deallocates the top and middle block,
 so the top and middle node need to get combined together. then allocates again to fill the rest of empty blocks.
*/
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

	print_memory(0);
	return;
}

/* TEST 5: COALESCE BOTTOM allocates 5 blocks, then deallocates the middle and bottom block,
 so the bottom and middle node need to get combined together. then allocates again.
*/
void test5_worst_fit()
{
	//alloc and dealloc -- coalesce bottom
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

	print_memory(0);
	return;
}

/* TEST 6: COALESCE BOTH - allocates 3 blocks then deallocates the top and middle block which need to get combined together.
then three additional blocks are allocated. then the first two of those three are deallocated 
and finally the one remaining block at the bottom is deallocated which results in all of them 
needing to be combined back together into one empty node
*/
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

	print_memory(1);
	return;
}

/////////////////////////////////
/* TEST 1: allocates two blocks, leaving one empty with remaining space
*/
void test1_best_fit() {
	//simple alloc only test
	printf("\nTest 1 worst Fit - expected states: 1 1 0\n");
	best_fit_memory_init(1000);
	best_fit_alloc(499);
	best_fit_alloc(159);
	print_memory(1);
	return;
}

/* TEST 2: allocates 4 blocks which completely fill the memory,
	tries to allocate a fifth but is unsuccesful because there is no space
*/
void test2_best_fit() {
	//alloc full test
	printf("\nTest 2 worst Fit - expected states: 1 1 1\n");
	best_fit_memory_init(1000);
	best_fit_alloc(299);
	best_fit_alloc(199);
	best_fit_alloc(428);
	// ---- full--------
	best_fit_alloc(100);
	best_fit_alloc(100);
	print_memory(1);
	return;
}

/* TEST 3: allocates 3 blocks then deallocates the top block,
	then allocates two more blocks tomake sure allcoation works after deallocation
*/
void test3_best_fit() {
	//simple alloc and dealloc - no coalescing required
	printf("\nTest 3 worst Fit - expected states 1 1 1 1\n");
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
	print_memory(1);
	return;
}

/* TEST 4: COALESCE TOP - allocates 3 blocks, then deallocates the top and middle block,
 so the top and middle node need to get combined together. then allocates again to fill the rest of empty blocks.
*/
void test4_best_fit()
{
	//alloc and dealloc -- coalesce top
	printf("\nTest 4 worst Fit - expected states: 1 1 1\n");
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

	print_memory(1);
	return;
}

/* TEST 5: COALESCE BOTTOM allocates 5 blocks, then deallocates the middle and bottom block,
 so the bottom and middle node need to get combined together. then allocates again.
*/
void test5_best_fit()
{
	//alloc and dealloc -- coalesce top
	printf("\nTest 5 worst Fit - expected states: 1 1 1 1 0\n");
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

	print_memory(1);
	return;
}

/* TEST 6: COALESCE BOTH - allocates 3 blocks then deallocates the top and middle block which need to get combined together.
then three additional blocks are allocated. then the first two of those three are deallocated 
and finally the one remaining block at the bottom is deallocated which results in all of them 
needing to be combined back together into one empty node
*/
void test6_best_fit()
{
	//alloc and dealloc -- coalesce top and bottom
	printf("\nTest 6 worst Fit - expected states: 0\n");
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

	print_memory(1);
	return;
}

//Worst Best - various sized (small and big) allocations and deallocations to compare fragmentation
void worst_best_test1()
{
	//----------Worst Fit ---------------
	worst_fit_memory_init(2000);
	void * worst_a = worst_fit_alloc(996);
	void * worst_b = worst_fit_alloc(8);

	worst_fit_dealloc(worst_a);

	void * worst_one = worst_fit_alloc(200);
	void * worst_two = worst_fit_alloc(224);
	void * worst_three = worst_fit_alloc(140);
	void * worst_four = worst_fit_alloc(200);
	void * worst_five = worst_fit_alloc(20);
	void * worst_six = worst_fit_alloc(24);
	void * worst_seven = worst_fit_alloc(28);
	void * worst_eight = worst_fit_alloc(32);
	void * worst_nine = worst_fit_alloc(36);
	void * worst_ten = worst_fit_alloc(40);
	void * worst_eleven = worst_fit_alloc(48);
	void * worst_twelve = worst_fit_alloc(124);
	void * worst_thirteen = worst_fit_alloc(180);
	void * worst_fourteen = worst_fit_alloc(8);

	worst_fit_dealloc(worst_six);
	worst_fit_dealloc(worst_eight);
	worst_fit_dealloc(worst_nine);
	worst_fit_dealloc(worst_twelve);

	//----------Best Fit ---------------
	best_fit_memory_init(2000);
	void * best_a = best_fit_alloc(996);
	void * best_b = best_fit_alloc(8);

	best_fit_dealloc(best_a);

	void * best_one = best_fit_alloc(200);
	void * best_two = best_fit_alloc(224);
	void * best_three = best_fit_alloc(140);
	void * best_four = best_fit_alloc(200);
	void * best_five = best_fit_alloc(20);
	void * best_six = best_fit_alloc(24);
	void * best_seven = best_fit_alloc(28);
	void * best_eight = best_fit_alloc(32);
	void * best_nine = best_fit_alloc(36);
	void * best_ten = best_fit_alloc(40);
	void * best_eleven = best_fit_alloc(48);
	void * best_twelve = best_fit_alloc(124);
	void * best_thirteen = best_fit_alloc(180);
	void * best_fourteen = best_fit_alloc(8);

	best_fit_dealloc(best_six);
	best_fit_dealloc(best_eight);
	best_fit_dealloc(best_nine);
	best_fit_dealloc(best_twelve);

	printf("Fragmentation Test - small and large allocations\n");
	printf("\nWorst Fit fragmentation under 8: %d", worst_fit_count_extfrag(8));
	printf("\nWorst Fit fragmentation under 32: %d", worst_fit_count_extfrag(32));
	printf("\nWorst Fit fragmentation under 48: %d", worst_fit_count_extfrag(48));
	printf("\nWorst Fit fragmentation under 64: %d", worst_fit_count_extfrag(64));
	printf("\nWorst Fit fragmentation under 80: %d", worst_fit_count_extfrag(80));
	printf("\nWorst Fit fragmentation under 128: %d", worst_fit_count_extfrag(128));
	printf("\nWorst Fit fragmentation under 256: %d", worst_fit_count_extfrag(256));
	printf("\nWorst Fit fragmentation under 512: %d", worst_fit_count_extfrag(512));
	printf("\n\n");

	printf("\nBest Fit fragmentation under 8: %d", best_fit_count_extfrag(8));
	printf("\nBest Fit fragmentation under 32: %d", best_fit_count_extfrag(32));
	printf("\nBest Fit fragmentation under 48: %d", best_fit_count_extfrag(48));
	printf("\nBest Fit fragmentation under 64: %d", best_fit_count_extfrag(64));
	printf("\nBest Fit fragmentation under 80: %d", best_fit_count_extfrag(80));
	printf("\nBest Fit fragmentation under 128: %d", best_fit_count_extfrag(128));
	printf("\nBest Fit fragmentation under 256: %d", best_fit_count_extfrag(256));
	printf("\nBest Fit fragmentation under 512: %d", best_fit_count_extfrag(512));
	printf("\n\n");


	return;
}

/* Worst Best - small sized data allocations and deallocations to compare fragmentation
*/
void worst_best_test2()
{
	//---WORST---
	worst_fit_memory_init(1000);
	void * worst_a = worst_fit_alloc(400);
	void * worst_b = worst_fit_alloc(8);

	worst_fit_dealloc(worst_a);
	
	//allocate a few
	void * b = worst_fit_alloc(16);
	void * c = worst_fit_alloc(32);
	void * d = worst_fit_alloc(8);
	void * e = worst_fit_alloc(40);
	void * f = worst_fit_alloc(28);
	void * g = worst_fit_alloc(56);

	worst_fit_dealloc(c);
	worst_fit_dealloc(f);
	worst_fit_dealloc(g);

	void * h = worst_fit_alloc(56);
	void * i = worst_fit_alloc(8);
	void * j = worst_fit_alloc(32);
	void * k = worst_fit_alloc(80);
	void * l = worst_fit_alloc(12);

	worst_fit_dealloc(i);
	worst_fit_dealloc(j);

	//BEST
	best_fit_memory_init(1000);
	void * best_a = best_fit_alloc(400);
	void * best_b = best_fit_alloc(8);

	best_fit_dealloc(best_a);
	
	//allocate a few
	void * bb = best_fit_alloc(16);
	void * bc = best_fit_alloc(32);
	void * bd = best_fit_alloc(8);
	void * be = best_fit_alloc(40);
	void * bf = best_fit_alloc(28);
	void * bg = best_fit_alloc(56);

	best_fit_dealloc(bc);
	best_fit_dealloc(bf);
	best_fit_dealloc(bg);

	void * bh = best_fit_alloc(56);
	void * bi = best_fit_alloc(8);
	void * bj = best_fit_alloc(32);
	void * bk = best_fit_alloc(80);
	void * bl = best_fit_alloc(12);

	best_fit_dealloc(bi);
	best_fit_dealloc(bj);

	printf("Fragmentation Test - small allocations\n");
	printf("\nWorst Fit fragmentation under 8: %d", worst_fit_count_extfrag(8));
	printf("\nWorst Fit fragmentation under 12: %d", worst_fit_count_extfrag(12));
	printf("\nWorst Fit fragmentation under 16: %d", worst_fit_count_extfrag(16));
	printf("\nWorst Fit fragmentation under 20: %d", worst_fit_count_extfrag(20));
	printf("\nWorst Fit fragmentation under 28: %d", worst_fit_count_extfrag(28));
	printf("\nWorst Fit fragmentation under 32: %d", worst_fit_count_extfrag(32));
	printf("\nWorst Fit fragmentation under 56: %d", worst_fit_count_extfrag(56));
	printf("\nWorst Fit fragmentation under 84: %d", worst_fit_count_extfrag(84));
	printf("\n\n");

	printf("\nBest Fit fragmentation under 8: %d", best_fit_count_extfrag(8));
	printf("\nBest Fit fragmentation under 12: %d", best_fit_count_extfrag(12));
	printf("\nBest Fit fragmentation under 16: %d", best_fit_count_extfrag(16));
	printf("\nBest Fit fragmentation under 20: %d", best_fit_count_extfrag(20));
	printf("\nBest Fit fragmentation under 28: %d", best_fit_count_extfrag(28));
	printf("\nBest Fit fragmentation under 32: %d", best_fit_count_extfrag(32));
	printf("\nBest Fit fragmentation under 56: %d", best_fit_count_extfrag(56));
	printf("\nBest Fit fragmentation under 84: %d", best_fit_count_extfrag(84));
	printf("\n\n");
}

//¯\_(⊙_ʖ⊙)_/¯
int main(int argc, char *argv[]) {
	// worst fit tests
	// printf("\n---BEST FIT TESTS---\n");
	// test1_worst_fit();
	// test2_worst_fit();
	// test3_worst_fit();
	// test4_worst_fit();
	// test5_worst_fit();
	// test6_worst_fit();

	// //best fit tests
	// printf("\n---WORST FIT TESTS---\n");
	// test1_best_fit();
	// test2_best_fit();
	// test3_best_fit();
	// test4_best_fit();
	// test5_best_fit();
	// test6_best_fit();

	//comparison tests
	 printf("\n---FRAGMENTATION TESTS---\n");
	 worst_best_test1();
	 worst_best_test2();

	return 0;
}