/*
 * scheduler_task.h
 *
 *  Created on: Nov 18, 2022
 *      Author:Qui
 */

#ifndef INC_SCHEDULER_HELPER_H_
#define INC_SCHEDULER_HELPER_H_

#include "stdlib.h"
#include "stdint.h"
//#include "scheduler.h"

#define TICK			10

typedef struct {
	void 	(*pTask)(uint32_t);
	uint32_t	led_index;
	uint32_t 	Delay;
	uint32_t	Period;
	uint8_t	RunMe;

	uint32_t TaskID;
	struct schedTask *nextTask;
} schedTask;

schedTask* make(void (*pTask)(uint32_t), uint32_t led_index, const uint32_t DELAY, const uint32_t PERIOD);
void delete(schedTask *task);

#endif /* INC_SCHEDULER_HELPER_H_ */
