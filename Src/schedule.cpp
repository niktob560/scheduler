#include "schedule.hpp"

namespace schedule
{
struct Task tasksMainLoop[scheduleQueueMaxLen];		   		//80 bytes
struct Task tasksAdditOnce[scheduleAdditQueueOnceMaxLen]; 	//16 bytes

uint16_t 	scheduleCounter = 0, 				//2 bytes
			scheduleQueueLen = 0,			   	//2 bytes
			subscheduleQueueLen = 0;		   	//2 bytes
uint8_t 	quantsElapsed;						//1 byte


void scheduleAddFunc(void (*func)())
{
	scheduleAddTask({func, 1});
}

void scheduleAddOnceFunc(void (*func)())
{
	scheduleAddOnceTask({func, 1});
}


void scheduleAddOnceTask(const struct Task task)
{
#ifdef TRY_SORT
	for (uint16_t i = 0; i < scheduleAdditQueueLen; i++)
	{
		if (tasksAdditOnce[i].func == 0)	//if found empty slot for task
		{
			ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
			{
				tasksAdditOnce[i] = task;	//put task to empty slot and exit function
			}
			return;
		}
	}
#endif //ifdef TRY_SORT
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		if (scheduleAdditQueueLen < scheduleAdditQueueOnceMaxLen)	//add to last elem of queue
		{
			tasksAdditOnce[scheduleAdditQueueLen] = task;
			scheduleAdditQueueLen++;
		}
	}
}


void scheduleAddTask(const struct Task task)
{
#ifdef TRY_SORT
	for (uint16_t i = 0; i < scheduleQueueLen; i++)
	{
		if (tasksMainLoop[i].func == 0)
		{
			ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
			{
				tasksMainLoop[i] = task;
			}
			return;
		}
	}
#endif //ifdef TRY_SORT
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		if (scheduleQueueLen < scheduleQueueMaxLen)
		{
			tasksMainLoop[scheduleQueueLen] = task;
			scheduleQueueLen++;
		}
	}
}


void _setTaskQueue(const struct Task tasks[], const size_t len)
{
	for (size_t i = 0; i < scheduleQueueMaxLen; i++)
		if (i < len)
			tasksMainLoop[i] = tasks[i];
		else if (i < scheduleQueueLen)
			tasksMainLoop[i].func = 0;
		else
			break;
	scheduleQueueLen = len;
}

void _setTaskQueue(void (*funcs[])(), const size_t len)
{
	for (size_t i = 0; i < scheduleQueueMaxLen; i++)
		if (i < len)
		{
			tasksMainLoop[i].func = funcs[i];
			tasksMainLoop[i].quantsWanted = 1;
		}
		else if (i < scheduleQueueLen)
			tasksMainLoop[i].func = 0;
		else
			break;
	scheduleQueueLen = len;
}

void _setOnceTaskQueue(const struct Task tasks[], const size_t len)
{
	for (size_t i = 0; i < scheduleAdditQueueLen; i++)
		if(i < len)
			tasksAdditOnce[i] = tasks[i];
		else if (i < scheduleAdditQueueLen)
			tasksAdditOnce[i] = {0,0};
		else
			break;
	scheduleAdditQueueLen = len;
}

void _setOnceTaskQueue(void (*funcs[])(), const size_t len)
{
	for (size_t i = 0; i < scheduleAdditQueueLen; i++)
		if(i < len)
		{
			tasksAdditOnce[i].func = funcs[i];
			tasksAdditOnce[i].quantsWanted = 1;
		}
		else if (i < scheduleAdditQueueLen)
			tasksAdditOnce[i] = {0,0};
		else
			break;
	scheduleAdditQueueLen = len;
}

} //namespace schedule
