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
		/* os_maxtaskrun specifies the maximum number of tasks that can be active at the same time. 
			 This includes tasks in any state (running, waiting, or ready) other than the INACTIVE state.*/
	
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
		U32 total_stack_size;
		U32 task_occupied_size = 0;
	
		//get current task from TCB which starts from index 0
		P_TCB task_content = os_active_TCB[task_id - 1];
		
		//invalid parameters
		if(task_content == NULL || task_id > os_maxtaskrun)
		{
			return(OS_R_NOK);
		}
			//fill p_task_info with all the information
			p_task_info -> task_id = task_id ;
			p_task_info -> state = task_content -> state; 
			p_task_info -> prio = task_content -> prio;
			p_task_info -> ptask = task_content -> ptask;
		
		if(task_content->priv_stack > 0)
		{
			total_stack_size = (U16)task_content->priv_stack;
		}
		else
		{
			total_stack_size = (U16)os_stackinfo;
		}
		
		//stack usage
		if(task_content -> state == RUNNING)
		{			
			//PSP points to the last item added in stack
			//task_content->stack points to the starting location of the task stack
			
			//task_content -> stack + total_stack_size gives us the last address of the stack
			//then subtracting PSP from the last address gives us size of the used space
			task_occupied_size = (U32)(task_content -> stack) + total_stack_size - (U32)(rt_get_PSP());
		}
		else
		{
			task_occupied_size = (U32)(task_content -> stack) + total_stack_size - (U32)(task_content->tsk_stack);
		}
		  
		// store stack percentage of used / total
		p_task_info -> stack_usage = (U8)((task_occupied_size*100)/ total_stack_size);
		
				
		return OS_R_OK;
		
}
/* end of file */
 
