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
		
		
	
		//if active count is greater than max, just return max
	return 0;
}

/*----------------------- rt_tsk_get --------------------------------*/
OS_RESULT rt_tsk_get (OS_TID task_id, RL_TASK_INFO *p_task_info) {
	// add your own code here
	return OS_R_OK;
}
/* end of file */
 