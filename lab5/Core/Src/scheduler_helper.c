/*
 * scheduler_task.c
 *
 *  Created on: Nov 18, 2022
 *      Author: Qui
 */

#include "scheduler_helper.h"

schedTask* make(void (*pTask)(uint32_t), uint32_t led_index, const uint32_t DELAY, const uint32_t PERIOD){
	schedTask *task = malloc(sizeof (schedTask));
	task->pTask = pTask;
	task->led_index = led_index;
	task->Delay = DELAY / TICK;
	task->Period = PERIOD / TICK;
	task->RunMe = 0;
	task->nextTask = NULL;
	return task;
}

void delete(schedTask *task){
	free(task);
}
