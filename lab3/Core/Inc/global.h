/*
 * global.h
 *
 *  Created on: 13 thg 11, 2022
 *      Author: Qui
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "software_timer.h"
#include "input_reading.h"

extern int flagTimer1;
extern int current_mode;

extern int traffic_duration[3];
extern int traffic_state[2];
extern int cur_time[2];
extern int traffic_time_buffer[2][2];

#endif /* INC_GLOBAL_H_ */
