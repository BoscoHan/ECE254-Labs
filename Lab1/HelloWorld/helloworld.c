//Lab1
//v9malhot 20662020
//y95han	20651352
#include <LPC17xx.h>
#include <RTL.h>
#include <stdio.h>
#include "uart_polling.h"
#include "../RTX_CM3/INC/RTL_ext.h"
#include <stdlib.h>

//prints the state of the task given the integer equiavalent
void printState(unsigned int state)
{
	switch (state) {
	case INACTIVE:
		printf("INACTIVE");
		break;
	case READY:
		printf("READY   ");
		break;
	case RUNNING:
		printf("RUNNING ");
		break;
	case WAIT_DLY:
		printf("WAIT_DLY");
		break;
	case WAIT_ITV:
		printf("WAIT_ITV");
		break;
	case WAIT_OR:
		printf("WAIT_OR ");
		break;
	case WAIT_AND:
		printf("WAIT_AND");
		break;
	case WAIT_SEM:
		printf("WAIT_SEM");
		break;
	case WAIT_MBX:
		printf("WAIT_MBX");
		break;
	case WAIT_MUT:
		printf("WAIT_MUT");
		break;
	default:
		printf("UNKNOWN ");    
	}
}

__task void task1()
{
	unsigned int i = 0;
	//uart0_put_string("Bosco and Vyom Lab 1");
	for(;;i++)
	{
		#ifdef MYSIM
		os_dly_wait(20);
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
		printf("\n\n\nActive Tasks:%d\n",count);
		printf("\tSTATES\t\tPRIORITY\tTID\tSTACK USAGE");
		printf("\n------------------------------------------------------------");
		
		for(i = 2; i< (count + 2); i++)
		{
			if(os_tsk_get(i, &taskInfo) == OS_R_OK)
			{
					printf("\nTask %d: ", i-1);
					printState(taskInfo.state);
					printf("\t%d\t",taskInfo.prio);
					printf("\t%d\t",taskInfo.task_id);
					printf("\t%d%%\t",taskInfo.stack_usage);
			}
			else
			{
				printf("Task %d: not okay\n", i-1);
			}
		}
		
		//delay
		#ifdef MYSIM
		os_dly_wait(7);
		#else
		os_dly_wait(1000);
		#endif
	}
}

__task void task3()
{
	while(1)
	{
		//delay
		#ifdef MYSIM
		os_dly_wait(20);
		#else
		os_dly_wait(300);
		#endif
	}
}

__task void task4()
{	
	// Fill stack with identifying values
	U8 t[440];
	U32 i = 0;
	// Fill the stack with 0xAA's (see in Memory window of debugger)
	t[0] = 0xAA;
	for(i=1;i<sizeof(t)/sizeof(U8);i++) {
		t[i] = t[i-1];
	}
	// Keep the task running forever
	for(i=0;; i++){}
}

__task void task5()
{
	//allocate space to test stack usage:
	int myArray[20] = { 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int myArray2[20] = { 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int i = 0;	
	
	for(;;i++)
	{
		i = myArray[19];
		i = myArray2[19];
		//delay
		#ifdef MYSIM
		os_dly_wait(20);
		#else
		os_dly_wait(1000);
		#endif
	}
}

__task void init(void)
{
	os_tsk_create(task1, 1); //task 1, priority 1
	os_tsk_create(task2, 1); //task 2, priority 1
	os_tsk_create(task3, 2); //task 3, priority 2
	os_tsk_create(task4, 1); //task 4, priority 1
	os_tsk_create(task5, 1); //task 5, priority 1
	os_tsk_delete_self(); //delete itself before exiting
}

int main()
{
	SystemInit();
	uart0_init();
	os_sys_init(init);
	return 0; 
}
