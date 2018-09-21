/**
 * @file:   rt_Task_ext.c
 */
#include "rt_TypeDef.h"
#include "RTX_Config.h"
#include "rt_System.h"
#include "rt_Task.h"
#include "rt_List.h"
#include "rt_Robin.h"
#include "rt_HAL_CM.h"
#include "rt_Task_ext.h"

/*----------------------- rt_tsk_count_get --------------------------*/
/* added for ECE254 lab */
// 
int rt_tsk_count_get (void) {
		// add your own code here
		/* specifies the maximum number of tasks that can be active at the same time. 
			 This includes tasks in any state (running, waiting, or ready) other than the INACTIVE state.*/
		
		//P_TCB *current = os_active_TCB;
		
	  int i;
		int activeTasks = 0;
		P_TCB current = *os_active_TCB;
	
		for(i=0; i < os_maxtaskrun; i++)
			{
				if(current != NULL && current->state != INACTIVE)
				{
					activeTasks++;
				}
				
				current = os_active_TCB[i+1];
			}
	return activeTasks;
}

/*----------------------- rt_tsk_get --------------------------------*/
	OS_RESULT rt_tsk_get (OS_TID task_id, RL_TASK_INFO *p_task_info) {
	// add your own code here
	P_TCB task_content;
	
	//assuming task_id -1 is the index of the task in array
	if(task_id > os_maxtaskrun || os_active_TCB[task_id-1] == NULL)
	{
		return OS_R_NOK;
	}
	
	task_content = os_active_TCB[task_id - 1];
	p_task_info -> state = task_content -> state; 
	p_task_info -> prio = task_content -> prio;
	p_task_info -> task_id;
	p_task_info -> ptask = task_content -> ptask;
	
	//p_task_info -> stack_usage
	
	return OS_R_OK;
}
/* end of file */
 
