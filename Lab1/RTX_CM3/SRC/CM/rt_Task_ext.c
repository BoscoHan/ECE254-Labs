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
		U32 total_stack_size;
		U32 task_occupied_size = 0;
		
		// add your own code here
		P_TCB task_content = os_active_TCB[task_id - 1];
		
		if(task_content == NULL || task_id > os_maxtaskrun)
		{
			return(OS_R_NOK);
		}
		
			p_task_info -> task_id = task_id ;
			p_task_info -> state = task_content -> state; 
			p_task_info -> prio = task_content -> prio;
			p_task_info -> ptask = task_content -> ptask;
		
		total_stack_size = (U16)os_stackinfo;
		
		//stack usage
		if(task_content -> state == RUNNING)
		{
			//task_occupied_size = (U32)rt_get_PSP() - (U32)task_content->stack;
			
			//PSP points to the last item in stack
			//task_content->stack points to the starting location of the task in the stack
			//PSP - task_content->stack is the space unused by that task
			//total_stack_size - unused stack space = space occupied by task
			task_occupied_size = total_stack_size - ((U32)rt_get_PSP() - (U32)task_content->stack);
		}
		else
		{
			task_occupied_size = total_stack_size - ((U32)task_content->tsk_stack - (U32)task_content->stack);
		}
		
// 		p_task_info -> stack_usage = (U8) ((task_occupied_size / total_stack_size)*100);
		  
		  // percentage of used / total
		  p_task_info -> stack_usage = (U8)((task_occupied_size/ total_stack_size)*100);
		
				
		return OS_R_OK;
		
// 		P_TCB task_content = os_active_TCB[task_id - 1];
// 		if(task_content != NULL)
// 		{
// 			
// 			p_task_info -> task_id = task_id ;
// 			p_task_info -> state = task_content -> state; 
// 			p_task_info -> prio = task_content -> prio;
// 			p_task_info -> ptask = task_content -> ptask;
// 			
// 		}
// 		
// 		if(task_content == NULL)
// 		{
// 			return(OS_R_NOK);
// 		}
// 		
// 		return OS_R_OK;
}
/* end of file */
 
