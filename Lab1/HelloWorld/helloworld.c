#include <LPC17xx.h>
#include <RTL.h>
#include <stdio.h>
#include "uart_polling.h"

__task void task1()
{
	unsigned int i = 0;
	
	for(;;i++)
	{
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
	while(1)
	{
		printf("Task2: HelloWorld!\n");
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
