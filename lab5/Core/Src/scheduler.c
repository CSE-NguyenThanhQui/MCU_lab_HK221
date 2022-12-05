/*
 * scheduler_ptr.c
 *
 *  Created on: Nov 18, 2022
 *      Author: Qui
 */

#include "scheduler.h"
#include "main.h"
#include "global.h"
//#include "scheduler_helper.h"

schedList SCH_tasks_G;
schedQueue SCH_queue;
uint32_t time;
uint32_t SCH_task_ID;

void SCH_Init(){
	SCH_tasks_G.cur_size = 0;
	SCH_tasks_G.head = NULL;
	time = 0;
	SCH_task_ID = 0;
	SCH_queue.head = NULL;
	SCH_queue.tail = NULL;
}

//hien thuc danh sach lien ket
void SCH_Add_To_List(schedTask *task){
	if (SCH_tasks_G.cur_size == SCH_MAX_TASKS) return;
	SCH_tasks_G.cur_size++;
	//them task dau tien
	if (SCH_tasks_G.cur_size == 1){
		SCH_tasks_G.head = task;
		return;
	}
	uint32_t time_interval = 0;
	schedTask *currTask = SCH_tasks_G.head,
			  *prevTask = NULL;
	while(currTask) {
		time_interval += currTask->Delay;
		if (task->Delay < time_interval) break;
		prevTask = currTask;
		currTask = currTask->nextTask;
	}
	if (prevTask == NULL) { //them vao dau
		SCH_tasks_G.head->Delay -= task->Delay;
		task->nextTask = SCH_tasks_G.head;
		SCH_tasks_G.head = task;
		return;
	}
	if (currTask == NULL) { //them vao cuoi
		task->Delay -= time_interval;
	}
	else { //them vao giua
		uint32_t tmp = task->Delay;
		task->Delay -= (time_interval - currTask->Delay);
		currTask->Delay = time_interval - tmp;
	}
	task->nextTask = currTask;
	prevTask->nextTask = task;
}
//lay ra phan tu dau tien trong danh sach
schedTask* SCH_Get_From_List(){
	schedTask *task = SCH_tasks_G.head;
	SCH_tasks_G.head = task->nextTask;
	task->nextTask = NULL;
	SCH_tasks_G.cur_size--;
	return task;
}

//hien thuc hang doi

void SCH_queue_push(schedTask *task) {
	if (SCH_queue.head == NULL) {
		SCH_queue.head = task;
	}
	else {
		SCH_queue.tail->nextTask = task;
	}
	SCH_queue.tail = task;
}

schedTask* SCH_queue_pop() {
	if (SCH_queue.head == NULL) return NULL;
	schedTask *task = SCH_queue.head;
	SCH_queue.head = task->nextTask;
	return task;
}


void SCH_Update(void){ //push task vao queue
	time += TICK; //tham so cho UART
	//xu ly phan tu head trong queue
	if (SCH_tasks_G.head){
		if (SCH_tasks_G.head->Delay == 0) {
			//the task is due to run
			SCH_tasks_G.head->RunMe = 1; //tin hieu RunMe cho phep task thuc hien
			if (SCH_tasks_G.head->Period){

				SCH_tasks_G.head->Delay = SCH_tasks_G.head->Period;
			}
			schedTask *runableTask = SCH_Get_From_List();
			SCH_queue_push(runableTask);
		}
		else {
			//chua duoc thuc hien
			SCH_tasks_G.head->Delay -= 1;
		}
	}
}

void SCH_Dispatch_Tasks(void){ //lay ra khoi queue
	schedTask *runningTask = SCH_queue_pop();
	if (runningTask) {
		Digit_UART("Task: ", runningTask->TaskID);
		Digit_UART("Start at: ", time);
		(*runningTask->pTask)(runningTask->led_index);
		Digit_UART("End at: ", time);

		if (runningTask->Period != 0){
			runningTask->RunMe = 0;
			SCH_Add_To_List(runningTask);
		}
		else {
			Str_UART("Task died...");
		}
	}
}


void SCH_Add_Task(void (*pTask)(uint32_t), uint32_t led_index, const uint32_t DELAY, const uint32_t PERIOD){
	if (SCH_tasks_G.cur_size == SCH_MAX_TASKS){
		return;
	}
	schedTask *newTask = make(pTask, led_index, DELAY, PERIOD);
	newTask->TaskID = SCH_task_ID++;
	SCH_Add_To_List(newTask);
}

uint32_t SCH_Delete_Task(){
	uint32_t Return_code;
	if (SCH_tasks_G.head == NULL) {
		Return_code = RETURN_ERROR;
	}
	else {
		Return_code = RETURN_NORMAL;
		schedTask *delTask = SCH_Get_From_List();
		delete(delTask);
	}
	return Return_code;
}
