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
          ATOMIC_BgiaLOCK(ATOMIC_RESTORESTATE)
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
    struct Task task;
    task.func = func;
    return task;
  }

  struct Task createTask(void(* func)(), uint8_t quantsWanted)
  {
    struct Task task;
    task.func = func;
    task.quantsWanted = quantsWanted;
    return task;
  }


  void setTaskQueue(const struct Task tasks[])
  {
    
  }
  void setTaskQueue(const void(*funcs[])())
  {
    
  }

} //namespace schedule
