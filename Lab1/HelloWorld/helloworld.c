// #include <LPC17xx.h>
// #include "uart_polling.h" 
// #include <RTL.h>
// #include "../RTX_CM3/INC/RTL_ext.h" /* extended interface header file */
// #include <stdio.h>
// #include <string.h>

// #define NUM_FNAMES 7

// struct func_info {
//   void (*p)();      /* function pointer */
//   char name[16];    /* name of the function */
// };

// extern void os_idle_demon(void);
// __task void task1(void);
// __task void task2(void);
// __task void task3(void);
// __task void task4(void);
// __task void task5(void);
// __task void init (void);
// __task void test_task(void);
//  
// char *state2str(unsigned char state, char *str);
// char *fp2name(void (*p)(), char *str);

// OS_MUT g_mut_uart;
// OS_TID g_tid = 255;

// int  g_counter = 0;  // a global counter
// char g_str[16];
// char g_tsk_name[16];

// struct func_info g_task_map[NUM_FNAMES] = \
// {
//   /* os_idle_demon function ptr to be initialized in main */
//   {NULL,  "os_idle_demon"}, \
//   {task1, "task1"},   \
//   {task2, "task2"},   \
// 	{task3, "task3"},   \
//   {task4, "task4"},   \
//   {task5, "task5"},   \
//   {init,  "init" }
// };

// /* no local variables defined, use one global var */
// __task void task1(void)
// {
// 	printf("Task 1 still active!\n");
// 	for (;;) {
// 		g_counter++;
// 	}
// }


// /*--------------------------- task2 -----------------------------------*/
// /* checking states of all tasks in the system                          */
// /*---------------------------------------------------------------------*/
// __task void task2(void)
// { 
// 	for(;;) {
// 		U8 i=1;
// 		RL_TASK_INFO task_info;
// 		int j = 0;
// 		
// 		os_mut_wait(g_mut_uart, 0xFFFF);
// 		printf("TID\tNAME\t\tPRIO\tSTATE   \t%%STACK\n");
// 		os_mut_release(g_mut_uart);
// 			
// 		for(i = 0; i <= os_tsk_count_get(); i++) {
// 			if (os_tsk_get(i+1, &task_info) == OS_R_OK) {
// 					os_mut_wait(g_mut_uart, 0xFFFF);  
// 					printf("%d\t%s\t\t%d\t%s\t%d%%\n", \
// 								 task_info.task_id, \
// 								 fp2name(task_info.ptask, g_tsk_name), \
// 								 task_info.prio, \
// 								 state2str(task_info.state, g_str),  \
// 								 task_info.stack_usage);
// 					os_mut_release(g_mut_uart);
// 			} 
// 		}
// 			
// 		if (os_tsk_get(0xFF, &task_info) == OS_R_OK) {
// 			printf("%p", task_info.ptask);
// 				os_mut_wait(g_mut_uart, 0xFFFF);  
// 				printf("%d\t%s\t\t%d\t%s\t%d%%\n", \
// 							 task_info.task_id, \
// 							 fp2name(task_info.ptask, g_tsk_name), \
// 							 task_info.prio, \
// 							 state2str(task_info.state, g_str),  \
// 							 task_info.stack_usage);
// 				os_mut_release(g_mut_uart);
// 		}
// 		//Delay the program
// 		while (j < 1000000) {
// 			j = j + 1;
// 		}
// 	}
// }

// void task4() {
// 	printf("Task 4 Completed but still Active!\n");
// 	for(;;);
// }

// void task5() {
// 	printf("Task 5 Idly Waiting.\n");
// 	for(;;){
// 		os_dly_wait(1000);
// 	}
// }

// void task3() {
// 	printf("\nNumber of Active Tasks:%d\n", os_tsk_count_get());
// 	printf("Task 3 Completed but still Active!\n");
// 	for(;;);
// }


// /*--------------------------- init ------------------------------------*/
// /* initialize system resources and create other tasks                  */
// /*---------------------------------------------------------------------*/
// __task void init(void)
// {
// 	os_mut_init(&g_mut_uart);
//   
// 	os_mut_wait(g_mut_uart, 0xFFFF);
// 	printf("init: TID = %d\n", os_tsk_self());
// 	os_mut_release(g_mut_uart);
//   
// 	g_tid = os_tsk_create(task1, 1);  /* task 1 at priority 1 */
// 	os_mut_wait(g_mut_uart, 0xFFFF);
// 	printf("init: created task1 with TID %d\n", g_tid);
// 	os_mut_release(g_mut_uart);
//   
// 	g_tid = os_tsk_create(task2, 1);  /* task 2 at priority 1 */
// 	os_mut_wait(g_mut_uart, 0xFFFF);
// 	printf("init: created task2 with TID %d\n", g_tid);
// 	os_mut_release(g_mut_uart);
// 	
// 	g_tid = os_tsk_create(task3, 1);  /* task 3 at priority 1 */
// 	os_mut_wait(g_mut_uart, 0xFFFF);
// 	printf("init: created task3 with TID %d\n", g_tid);
// 	os_mut_release(g_mut_uart);
// 	
// 	g_tid = os_tsk_create(task4, 1);  /* task 4 at priority 1 */
// 	os_mut_wait(g_mut_uart, 0xFFFF);
// 	printf("init: created task4 with TID %d\n", g_tid);
// 	os_mut_release(g_mut_uart);
// 	
// 	g_tid = os_tsk_create(task5, 1);  /* task 5 at priority 1 */
// 	os_mut_wait(g_mut_uart, 0xFFFF);
// 	printf("init: created task5 with TID %d\n", g_tid);
// 	os_mut_release(g_mut_uart);
//   
// 	os_tsk_delete_self();     /* task MUST delete itself before exiting */
// }

// /**
//  * @brief: convert state numerical value to string represenation      
//  * @param: state numerical value (macro) of the task state
//  * @param: str   buffer to save the string representation, 
//  *               buffer to be allocated by the caller
//  * @return:the string starting address
//  */
// char *state2str(unsigned char state, char *str)
// {
// 	switch (state) {
// 	case INACTIVE:
// 		strcpy(str, "INACTIVE");
// 		break;
// 	case READY:
// 		strcpy(str, "READY   ");
// 		break;
// 	case RUNNING:
// 		strcpy(str, "RUNNING ");
// 		break;
// 	case WAIT_DLY:
// 		strcpy(str, "WAIT_DLY");
// 		break;
// 	case WAIT_ITV:
// 		strcpy(str, "WAIT_ITV");
// 		break;
// 	case WAIT_OR:
// 		strcpy(str, "WAIT_OR");
// 		break;
// 	case WAIT_AND:
// 		strcpy(str, "WAIT_AND");
// 		break;
// 	case WAIT_SEM:
// 		strcpy(str, "WAIT_SEM");
// 		break;
// 	case WAIT_MBX:
// 		strcpy(str, "WAIT_MBX");
// 		break;
// 	case WAIT_MUT:
// 		strcpy(str, "WAIT_MUT");
// 		break;
// 	default:
// 		strcpy(str, "UNKNOWN");    
// 	}
// 	return str;
// }

// /** 
//  * @brief: get function name by function pointer
//  * @param: p the entry point of a function (i.e. function pointer)
//  * @param: str the buffer to return the function name
//  * @return: the function name string starting address
//  */
// char *fp2name(void (*p)(), char *str)
// {
// 	int i;
// 	unsigned char is_found = 0;
//   
// 	for ( i = 0; i < NUM_FNAMES; i++) {
// 		if (g_task_map[i].p == p) {
// 			str = strcpy(str, g_task_map[i].name);  
// 			is_found = 1;
// 			break;
// 		}
// 	}
// 	if (is_found == 0) {
// 		strcpy(str, "ghost");
// 	}
// 	return str;
// }

// int main(void)
// {
// 	SystemInit();         /* initialize the LPC17xx MCU */
// 	uart0_init();         /* initilize the first UART */
//   
//   
// 	/* fill the fname map with os_idle_demon entry point */
// 	g_task_map[0].p = os_idle_demon;
//   
// 	printf("Calling os_sys_init()...\n");
// 	os_sys_init(init);    /* initilize the OS and start the first task */
// }

#include <LPC17xx.h>
#include <RTL.h>
#include <stdio.h>
#include "uart_polling.h"
#include "../RTX_CM3/INC/RTL_ext.h"
#include <stdlib.h>
// #include "../RTX_CM3/SRC/CM/rt_Task_ext.h"
//#include "../RTX_CM3/SRC/CM/rt_Task_ext.c"

__task void task1()
{
	unsigned int i = 0;
	for(;;i++)
	{
		RL_TASK_INFO taskInfo;
		os_tsk_get(2, &taskInfo);
		//RUNNING
		printf("Task1: %d\n", i);
		//just checking that its running from within the task------------------------------------------------------
		printf("Task 1 state: %d\n", taskInfo.state);
		// --------------------------------------------------------------------------------------------------------
		//delay
		#ifdef MYSIM
		os_dly_wait(1);
		#else
		os_dly_wait(100);
		#endif
	}
}

__task void task2()
{
	RL_TASK_INFO taskInfo;
	
	while(1)
	{
		int i;
		int count = os_tsk_count_get();
		printf("Active Tasks:%d\n",count);
		printf("Task2: STATES\n");
		
		for(i = 2; i< (count + 2); i++)
		{
			if(os_tsk_get(i, &taskInfo) == OS_R_OK)
			{
				if(taskInfo.state == RUNNING)
				{
					printf("Task %d: running\n", i-1);
				}
				else
				{
					printf("Task %d: not running\n", i-1);
				}
			}
			else
			{
				printf("Task %d: not okay\n", i-1);
			}
		}
		
		//delay
		#ifdef MYSIM
		os_dly_wait(3);
		#else
		os_dly_wait(300);
		#endif
	}
}

__task void task3()
{
	while(1)
	{
		printf("I am task 3\n");
		
		//delay
		#ifdef MYSIM
		os_dly_wait(3);
		#else
		os_dly_wait(300);
		#endif
	}
}

__task void task4()
{
	
	while(1)
	{
		//delay
		#ifdef MYSIM
		os_dly_wait(3);
		#else
		os_dly_wait(300);
		#endif
	}
}

__task void init(void)
{
	os_tsk_create(task1, 1); //task 1, priority 1
	os_tsk_create(task2, 1); //task 2, priority 1
	os_tsk_create(task3, 1); //task 3, priority 1
	os_tsk_create(task4, 1); //task 3, priority 1
	os_tsk_delete_self(); //delete itself before exiting
}

int main()
{
	SystemInit();
	uart0_init();
	os_sys_init(init);
	/* uart0_put_string("Hello World!\n\r");
	return 0; */	
}
