#include "schedule.hpp"

namespace schedule
{
struct Task tasksMainLoop[scheduleQueueMaxLen];		   		//80 bytes
struct Task tasksAdditOnce[scheduleAdditQueueOnceMaxLen]; 	//16 bytes

uint8_t 	quantsElapsed;						//1 byte

const struct Task	emptyTask = {0,0};
bool idle = false;

uint16_t 	scheduleCounter,								//2  bytes
			scheduleQueueLen,								//2  bytes
			scheduleAdditQueueLen;							//2  bytes








   
void removeTask(const struct Task task)
{
	for(size_t i = 0; i < scheduleQueueLen; i++)
	{
		if(tasksMainLoop[i] == task)
		{
			ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
			{
				tasksMainLoop[i] = emptyTask;
				if(i == scheduleQueueLen)
					scheduleQueueLen--;
			}
		}
	}
}


void removeFunc(void (*func)())
{
	removeTask({func, 1});
}


void removeTaskOnce(const struct Task task)
{
	for(size_t i = 0; i < scheduleAdditQueueLen; i++)
	{
		if(tasksAdditOnce[i] == task)
		{
			ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
			{
				tasksAdditOnce[i] = emptyTask;
				if(i == scheduleAdditQueueLen)
					scheduleAdditQueueLen--;
			}
		}
	}
}


void removeFuncOnce(void (*func)())
{
	removeTaskOnce({func, 1});
}





void addFunc(void (*func)())
{
	addTask({func, 1});
}

void addOnceFunc(void (*func)())
{
	addOnceTask({func, 1});
}


void addOnceTask(const struct Task task)
{
#ifdef TRY_SORT
	for (uint16_t i = 0; i < scheduleAdditQueueLen; i++)
	{
		if (tasksAdditOnce[i].quantsWanted == 0)	//if found empty slot for task
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


void addTask(const struct Task task)
{
#ifdef TRY_SORT
	for (uint16_t i = 0; i < scheduleQueueLen; i++)
	{
		if (tasksMainLoop[i].quantsWanted == 0)
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
			tasksMainLoop[i] = emptyTask;
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
			tasksMainLoop[i] = emptyTask;
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
			tasksAdditOnce[i] = emptyTask;
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
			tasksAdditOnce[i] = emptyTask;
		else
			break;
	scheduleAdditQueueLen = len;
}


inline bool isIndexInMainLoop(const size_t index)
{
	return index < scheduleQueueLen;
}

inline bool isIndexInAddinQueue(const size_t index)
{
	return index >= scheduleQueueLen && index < scheduleAdditQueueLen + scheduleQueueMaxLen;
}


void call(const size_t index)
{
	void (*func)() = 0x00;
	if(isIndexInMainLoop(scheduleCounter) && tasksMainLoop[index].quantsWanted != 0)								//get task from main loop
		func = tasksMainLoop[index].func;
	else if(isIndexInAddinQueue(scheduleCounter) && tasksAdditOnce[index - scheduleQueueMaxLen].quantsWanted != 0)	//get task from additional queue
		func = tasksMainLoop[index - scheduleQueueMaxLen].func;
	
	if(idle && func != 0x00)		//if can call new task and task exists
	{
		idle = false;
		func();
		idle = true;
	}
}

void schedule(void)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		if(isIndexInMainLoop(scheduleCounter))
		{
			//run task from main loop
			if(idle && quantsElapsed >= tasksMainLoop[scheduleCounter].quantsWanted)
			{
				quantsElapsed = 0;
				scheduleCounter++;
			}
			else
				quantsElapsed++;
		}
		else if(isIndexInAddinQueue(scheduleCounter))
		{
			//run task from once queue
			if(idle && quantsElapsed >= tasksAdditOnce[scheduleCounter - scheduleQueueLen].quantsWanted)
			{
				quantsElapsed = 0;
				scheduleCounter++;
			}
			else
				quantsElapsed++;
		}
		else if(idle)
		{
			//set counter to zero, flush additional once queue and run from start
			scheduleCounter = 0;
			quantsElapsed = 0;
			scheduleAdditQueueLen = 0;
		}
	}
	if(quantsElapsed == 0)
		call(scheduleCounter);
}

} //namespace schedule
