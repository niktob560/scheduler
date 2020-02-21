#include "schedule.hpp"

namespace schedule
{
  struct _Task       tasksMainLoop[scheduleQueueMaxLen];            //80 bytes
  struct _Task       tasksAdditOnce[scheduleAdditQueueOnceMaxLen];  //16 bytes

  volatile uint16_t scheduleCounter = 0,    //2 bytes
                    scheduleQueueLen = 0,		//2 bytes
                    subscheduleQueueLen = 0;//2 bytes

  /*
   *	Function:	scheduleAddFunc
   *	Desc:		  Add func to repeat by schedule (adding instead of idle)
   *	Input:		void* func: ptr to func
   *	Output:		none
   */
  void scheduleAddFunc(struct _Task task)
  {
    #ifdef TRY_SORT
      for(uint16_t i = 0; i < scheduleQueueLen; i++)
      {
        if(tasksMainLoop[i].func == 0)
        {
          ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
          {
            tasksMainLoop[i] = task;
          }
          return;
        }
      }
    #endif
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
      if(scheduleQueueLen < scheduleQueueLen)
      {
        tasksMainLoop[scheduleQueueLen] = task;
        scheduleQueueLen++;
      }
    }
  }

  
  struct Task createTask(void(* func)())
  {
    struct Task task = {func, 1};
    task.func = func;
    return task;
  }

  struct Task createTask(void(* func)(), uint8_t quantsWanted)
  {
    struct Task task = {func, quantsWanted};
    return task;
  }


  void _setTaskQueue(const struct Task tasks[], const size_t len)
  {
    for(size_t i = 0; i < scheduleQueueMaxLen; i++)
    {
      if(i < len)
      {
        tasksMainLoop[i].func = tasks[i].func;
        tasksMainLoop[i].quantsWanted = tasks[i].quantsWanted;
        tasksMainLoop[i].quantsElapsed = 0;
      }
      else
      {
        tasksMainLoop[i].func = 0;
      }
    }
  }

  void _setTaskQueue(void(*funcs[])(), const size_t len)
  {
    for(size_t i = 0; i < scheduleQueueMaxLen; i++)
    {
      if(i < len)
      {
        tasksMainLoop[i].func = funcs[i];
        tasksMainLoop[i].quantsWanted = 1;
        tasksMainLoop[i].quantsElapsed = 0;
      }
      else
      {
        tasksMainLoop[i].func = 0;
      }
    }
  }


} //namespace schedule
