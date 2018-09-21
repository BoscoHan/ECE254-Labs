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
	int count;
	for(;;i++)
	{
		
		count = rt_tsk_count_get(); 
		printf("Count: %d\n",count);
		printf("Task1: %d\n", i);
		#ifdef MYSIM
		os_dly_wait(1);
		#else
		os_dly_wait(100);
		#endif
	}
}

__task void task2()
{
	//OS_RESULT testGet;
	RL_TASK_INFO *taskInfo; //= malloc(64); //= malloc(sizeof(RL_TASK_INFO));
	
	while(1)
	{
		printf("Task2: HelloWorld!\n");
		//not actually filling taskInfo, just has garbage right now 
		rt_tsk_get(128, taskInfo);
		//testGet = rt_tsk_get(1, taskInfo);
		printf("state: %d\n", taskInfo->state);
		
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
